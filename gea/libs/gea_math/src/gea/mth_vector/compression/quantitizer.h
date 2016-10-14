#ifndef __GEA_MTH_VECTOR_QUANTITIZER_H__
#define __GEA_MTH_VECTOR_QUANTITIZER_H__

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_core/bits.h>

namespace gea {
namespace mth {

template <typename IN, typename OUT>
union union_cast {
    IN  in;
    OUT out;
};

template <typename T> struct ieee754_trait {};
template <> struct ieee754_trait<float> {
    typedef uint32_t int_type;
    typedef float    flt_type;

    static const int_type SIGN_SHIFT = 31;
    static const int_type SIGN_MASK  = 0x01;
    static const int_type EXP_SHIFT  = 23;
    static const int_type EXP_MASK   = 0xFF;
    static const int_type MANT_SHIFT = 0;
    static const int_type MANT_MASK  = 0x7FFFFF;
};
template <> struct ieee754_trait<double> {
    typedef uint64_t int_type;
    typedef double   flt_type;

    static const int_type SIGN_SHIFT = 63;
    static const int_type SIGN_MASK  = 0x01;
    static const int_type EXP_SHIFT  = 52;
    static const int_type EXP_MASK   = 0x7FF;
    static const int_type MANT_SHIFT = 0;
    static const int_type MANT_MASK  = 0xFFFFFFFFFFFFF;
};

template <typename T>
struct ieee754 {
    typedef typename ieee754_trait<T>::int_type int_type;
    typedef typename ieee754_trait<T>::flt_type flt_type;
    typedef union_cast<flt_type,int_type> cast;

    static const int_type SIGN_SHIFT = ieee754_trait<T>::SIGN_SHIFT;
    static const int_type SIGN_MASK  = ieee754_trait<T>::SIGN_MASK;
    static const int_type EXP_SHIFT  = ieee754_trait<T>::EXP_SHIFT;
    static const int_type EXP_MASK   = ieee754_trait<T>::EXP_MASK;
    static const int_type MANT_SHIFT = ieee754_trait<T>::MANT_SHIFT;
    static const int_type MANT_MASK  = ieee754_trait<T>::MANT_MASK;

    static inline const int_type get_int(const flt_type &x) { return ((cast *) &x)->out; }
    static inline const flt_type get_flt(const int_type &x) { return ((cast *) &x)->in; }

    static inline const int_type get_sign(const int_type &x) { return (x >> SIGN_SHIFT) & SIGN_MASK; }
    static inline const int_type get_exp (const int_type &x) { return (x >> EXP_SHIFT)  & EXP_MASK;  }
    static inline const int_type get_mant(const int_type &x) { return (x >> MANT_SHIFT) & MANT_MASK; }

    static inline const void set_sign(int_type &x, const int_type &sign) {
        x = (x & ~(SIGN_MASK << SIGN_SHIFT)) | (sign << SIGN_SHIFT);
    }
    static inline const void set_exp (int_type &x, const int_type &sign) {
        x = (x & ~(EXP_MASK << EXP_SHIFT)) | (sign << EXP_SHIFT);
    }
    static inline const void set_mant(int_type &x, const int_type &sign) {
        x = (x & ~(MANT_MASK << MANT_SHIFT)) | (sign << MANT_SHIFT);
    }
};











//struct test_param {
//    typedef float    in_type;
//    typedef uint32_t out_type;
//
//    static inline const out_type bits() { return 0; }
//    static inline const in_type  min() { return 0.0f; }
//    static inline const in_type  max() { return 0.0f; }
//};

template <typename PAR>
class qzer_fix {
public:
    typedef typename PAR::in_type  in_type;
    typedef typename PAR::out_type out_type;

    static inline const out_type quantitize(const in_type &x) {
        static const out_type enc_bits     = PAR::bits();
        static const in_type enc_max       = std::numeric_limits<out_type>::max();
        static const in_type enc_range_inv = 1.0f / (PAR::max() - PAR::min());

        in_type nx = mth::clamp( ((x - PAR::min()) * enc_range_inv), (in_type) 0, (in_type) 1);
        return (out_type) (nx * ((1 << enc_bits)-1));
    }
};

// scale float to the range [1,2[ and store only x bits of mantissa
template <typename PAR>
class qzer_ {
public:
    typedef typename PAR::in_type  in_type;
    typedef typename PAR::out_type out_type;

    //static inline const out_type quantitize(const in_type &x) {

    //}
    //static inline const IN dequantitize(const OUT &x) {
    //    return 
    //}
private:
    //static inline const OUT mask() { return gea::bit::mask(PAR::bits()); }
};




} // namespace mth //
} // namespace gea //

#endif // __GEA_MTH_VECTOR_QUANTITIZER_H__ //
