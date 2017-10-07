#ifndef __GEA_MTH_CORE_INTRINSIC_H__
#define __GEA_MTH_CORE_INTRINSIC_H__

// ------------------------------------------------------------------------- //
// x86 intrinsic functions                                                   //
// ------------------------------------------------------------------------- //

namespace gea {
namespace mth {
// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //
// trigonometry
inline void i_fsincos(float angle, float &out_sin, float &out_cos);

// attributes
inline const bool i_fisnan(const float number);
inline const bool i_ffinite(const float number);
    
} // namespace mth //
} // namespace gea //

#if   defined _MSC_VER
    #include "intrinsic_msvc.inl"
#elif defined __GNUC__
    #include "intrinsic_gcc.inl"
#else
    #error Unsupported compiler!
#endif

#endif // __GEA_MTH_CORE_INTRINSIC_H__ //
