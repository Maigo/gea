#ifndef __GEA_MTH_CORE_HALF_H__
#define __GEA_MTH_CORE_HALF_H__

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// half                                                                      //
// ------------------------------------------------------------------------- //
// info: 16 bit 2 based floating point precision type                        //
//                                                                           //
//          1 bit     sign     (s)                                           //
//          5 bits    exponent (e)                                           //
//         10 bits    fraction (f)                                           //
//                                                                           //
//         bias: 15    2^-14 - 2^15                                          //
//         (s) * (1.f) * 2 ^ (e - bias)                                      //
// ------------------------------------------------------------------------- //
class half {
public:
    // constants
    static const uint16_t HALF_ZERO;     // 0x00000000
    static const float    HALF_MAX;      // 65504.0f
    static const float    HALF_MIN;      // 6.10351562e-05f
    static const float    HALF_DNRM_MIN; // 5.96046448e-08f
    static const float    HALF_EPSILON;  // 0.00097656f

    // constructors
    inline half() : m_bits(HALF_ZERO) {}
    inline half(uint16_t bits) : m_bits(bits) {}
    half(const float &f);

    // typecast function
    operator float() const;

    // state functions
    inline bool is_zero() const;
    inline bool is_finite() const;
    inline bool is_negative() const;
    inline bool is_normalized() const;
    inline bool is_denormalized() const;
    inline bool is_infinity() const;
    inline bool is_nan() const;

    // internal represenation access functions
    inline uint16_t &bits();

    // compression functions
    inline static bool can_pack(const float &f);

private:
    // segment access
    // constants
    static const uint16_t HALF_SIGN_MASK = 0x8000;
    static const uint16_t HALF_EXP_MASK  = 0x7C00;
    static const uint16_t HALF_FRAC_MASK = 0x03FF;
    static const uint16_t HALF_SIGN_SHIFT = 15;
    static const uint16_t HALF_EXP_SHIFT  = 10;
    static const uint16_t HALF_FRAC_SHIFT =  0;
    // functions
    static inline const uint16_t HALF_SIGN_F(const uint16_t &x);
    static inline const uint16_t HALF_EXP_F (const uint16_t &x);
    static inline const uint16_t HALF_FRAC_F(const uint16_t &x);

    void convert(const uint32_t &i);
    inline float overflow() const;

    // internal representation
    uint16_t m_bits;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "half.inl"

#endif // __GEA_MTH_VECTOR_HALF_H__ //
