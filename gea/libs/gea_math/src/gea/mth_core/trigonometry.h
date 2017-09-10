#ifndef __GEA_MTH_CORE_TRIGONOMETRY_H__
#define __GEA_MTH_CORE_TRIGONOMETRY_H__

// gea includes
#include <gea/mth_core/base.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //
// conversion functions
inline const float degrees_to_radians(const float deg);
inline const float radians_to_degrees(const float rad);
// optimized sin & cos method
inline void fsincos(const float angle, float &out_sin, float &out_cos);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_angle_eq(const float a0, const float a1, const float e = APPROX_EPSILON);
inline const bool approx_angle_ne(const float a0, const float a1, const float e = APPROX_EPSILON);

} // namespace mth //
} // namespace gea //

#include "trigonometry.inl"

#endif // __GEA_MTH_CORE_TRIGONOMETRY_H__ //
