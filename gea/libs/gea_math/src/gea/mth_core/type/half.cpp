
// header include
#include "half.h"

namespace gea {
namespace mth {

namespace internal {

// template union cast
template <typename T1, typename T2>
union union_cast {
    T1 in;
    T2 out;
};
typedef union_cast<float,uint32_t> float_to_uint;

// IEEE754 32bit float bit access constants and functions
static const uint32_t FLOAT_SIGN_MASK = 0x80000000;
static const uint32_t FLOAT_EXP_MASK  = 0x7F800000;
static const uint32_t FLOAT_FRAC_MASK = 0x007FFFFF;
static const uint32_t FLOAT_SIGN_SHIFT = 31;
static const uint32_t FLOAT_EXP_SHIFT  = 23;
static const uint32_t FLOAT_FRAC_SHIFT =  0;

inline const uint32_t FLOAT_SIGN_F(const uint32_t &x) { return ((x & FLOAT_SIGN_MASK) >> FLOAT_SIGN_SHIFT); }
inline const uint32_t FLOAT_EXP_F (const uint32_t &x) { return ((x & FLOAT_EXP_MASK ) >> FLOAT_EXP_SHIFT ); }
inline const uint32_t FLOAT_FRAC_F(const uint32_t &x) { return ((x & FLOAT_FRAC_MASK) >> FLOAT_FRAC_SHIFT); }
inline const uint32_t FLOAT_INL_SIGN_F(const uint32_t &x) { return (x << FLOAT_SIGN_SHIFT); }
inline const uint32_t FLOAT_INL_EXP_F (const uint32_t &x) { return (x << FLOAT_EXP_SHIFT ); }
inline const uint32_t FLOAT_INL_FRAC_F(const uint32_t &x) { return (x << FLOAT_FRAC_SHIFT); }

} // namespace internal //

// constants
const uint16_t half::HALF_ZERO     = 0x00000000;
const float    half::HALF_MAX      = 65504.0f;
const float    half::HALF_MIN      = 6.10351562e-05f;
const float    half::HALF_DNRM_MIN = 5.96046448e-08f;
const float    half::HALF_EPSILON  = 0.00097656f;

// constructors
half::half(const float& f) {
    // union cast float to int
    register uint32_t i = ((const internal::float_to_uint *) &f)->out;

    // zero - preserv sign
    if (f == 0.0f) {
        m_bits = (i >> 16);
    } else {
        register uint32_t exp = internal::FLOAT_EXP_F(i) - (127 - 15);

        if (exp > 0 && exp < 30) { // float is normalized, nice!
            m_bits = (internal::FLOAT_SIGN_F(i) << 15) | (exp << 10) |
                     (internal::FLOAT_FRAC_F(i) >> 13) + ((internal::FLOAT_FRAC_F(i) >> 12) & 1);
        } else { // float is denormalized or just not nice
            convert(i);
        }
    }
}

// cast function
half::operator float() const {
    register uint32_t i;

    register uint32_t sign = HALF_SIGN_F(m_bits);
    register uint32_t exp  = HALF_EXP_F (m_bits);
    register uint32_t frac = HALF_FRAC_F(m_bits);

    // special case - zero or subnormal numbers
    if (exp == 0) {
        // + or - zero
        if (frac == 0) {
            i = sign << 31;
            // union cast int to float
            return ((const internal::float_to_uint *) &i)->in;
        // denormalized number (renormalize it)
        } else {
            while (!(frac & 0x400)) {
                frac <<= 1;
                --exp;
            }
            ++exp;
            frac &= ~0x400;
        }
    // special case - infinity or NaN
    } else if (exp == 31) {
        // positive or negative infinity
        if (frac == 0) {
            i = (sign << 31) | 0x7f800000;
            // union cast int to float
            return ((const internal::float_to_uint *) &i)->in;
        // NaN (preserve sign and significand bits)
        } else {
            // union cast int to float
            return ((const internal::float_to_uint *) &i)->in;
        }
    }

    // normalized number
    exp -= (15 - 127);

    // reassemble
    i = (sign << 31) | (exp << 23) | (frac << 13);
    // union cast int to float
    return ((const internal::float_to_uint *) &i)->in;
}

// private functions
void half::convert(const uint32_t &i) {
    register uint32_t sign =  (i >> 16) & 0x00008000;
    register  int32_t exp  = ((i >> 23) & 0x000000ff) - (127 - 15);
    register uint32_t frac =   i        & 0x007fffff;

    // reassemble sign, exp and frac into a half

    // exp is negative or zero
    if (exp <= 0) {
        // exp is less than HALF_DNRM_MIN (f may be a small normalized
        // float, a denormalized float or a zero). Preserve sign.
        if (exp < -10) {
            m_bits = (uint16_t) sign;
        } else {
            // E is between -10 and 0.  F is a normalized float
            // whose magnitude is less than HALF_MIN.

            // We convert f to a denormalized half.

            // Add an explicit leading 1 to the significand.
            frac = frac | 0x00800000;

            // Round to m to the nearest (10+e)-bit value (with e between
            // -10 and 0); in case of a tie, round to the nearest even value.

            // Rounding may cause the significand to overflow and make
            // our number normalized.  Because of the way a half's bits
            // are laid out, we don't have to treat this case separately;
            // the code below will handle it correctly.
            uint32_t t = 14 - exp;
            uint32_t a = (1 << (t - 1)) - 1;
            uint32_t b = (frac >> t) & 0x1;

            frac = (frac + a + b) >> t;

            // assemble the half from s, e (zero) and m.
            m_bits = sign | frac;
        }
    } else if (exp == 0xff - (127 - 15)) {
        if (frac == 0) {
            // F is an infinity; convert f to a half
            // infinity with the same sign as f.
            m_bits = sign | 0x7c00;
        } else {
            // F is a NAN; we produce a half NAN that preserves
            // the sign bit and the 10 leftmost bits of the
            // significand of f, with one exception: If the 10
            // leftmost bits are all zero, the NAN would turn 
            // into an infinity, so we have to set at least one
            // bit in the significand.
            frac >>= 13;
            m_bits = sign | 0x7c00 | frac | (frac == 0);
        }
    } else {
        // E is greater than zero.  F is a normalized float.
        // We try to convert f to a normalized half.

        // Round to m to the nearest 10-bit value.  In case of
        // a tie, round to the nearest even value.
        frac = frac + 0x00000fff + ((frac >> 13) & 0x1);

        if (frac & 0x00800000) {
            frac = 0; // overflow in significand,
            exp += 1; // adjust exponent
        }

        // Handle exponent overflow
        if (exp > 30) {
            overflow();             // cause a hardware floating point overflow
            m_bits = sign | 0x7c00; // if this returns, the half becomes an
                                    // infinity with the same sign as f.
        } else {
            // assemble the half
            m_bits = sign | (exp << 10) | (frac >> 13);
        }
    }
}

} // namespace mth //
} // namespace gea //
