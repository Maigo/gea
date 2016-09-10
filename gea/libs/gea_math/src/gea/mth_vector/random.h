#ifndef __GEA_VMTH_RANDOM_H__
#define __GEA_VMTH_RANDOM_H__

// mth includes
#include <gea/mth_vector/matrix3.h>
#include <gea/mth_vector/polar3.h>
#include <gea/mth_vector/quaternion.h>
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
// vector3                                                                   //
// ------------------------------------------------------------------------- //
inline const vector3 rand_vector3(const float max, const float min = 0.0f);

} // namespace mth //
} // namespace gea //

#include "random.inl"

#endif // __GEA_VMTH_RANDOM_H__ //
