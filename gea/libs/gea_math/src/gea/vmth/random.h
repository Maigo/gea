#ifndef __GEA_VMTH_RANDOM_H__
#define __GEA_VMTH_RANDOM_H__

// external includes
#include <gea/random/random.h>

// mth includes
#include <gea/vmth/matrix3.h>
#include <gea/vmth/polar3.h>
#include <gea/vmth/quaternion.h>
#include <gea/vmth/vector3.h>

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
inline const vector3 rand_vector3(float max, float min = 0.0f);

} // namespace mth //
} // namespace gea //

#include "random.inl"

#endif // __GEA_VMTH_RANDOM_H__ //
