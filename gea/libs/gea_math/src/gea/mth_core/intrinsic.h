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

} // namespace mth //
} // namespace gea //

#include "intrinsic.inl"

#endif // __GEA_MTH_CORE_INTRINSIC_H__ //
