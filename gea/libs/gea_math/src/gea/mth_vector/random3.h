#ifndef __GEA_MTH_VECTOR_RANDOM3_H__
#define __GEA_MTH_VECTOR_RANDOM3_H__

// gea includes
#include <gea/mth_vector/matrix3.h>
#include <gea/mth_vector/polar3.h>
#include <gea/mth_vector/quaternion.h>
#include <gea/mth_vector/point3.h>
#include <gea/mth_vector/vector3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// polar3                                                                    //
// ------------------------------------------------------------------------- //
inline const polar3 rand_polar3();

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
inline const quaternion rand_quaternion();

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
inline const vector3 rand_vector3(const float max_length, const float min_length = 0.0f);

} // namespace mth //
} // namespace gea //

#include "random3.inl"

#endif // __GEA_MTH_VECTOR_RANDOM3_H__ //
