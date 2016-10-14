#ifndef __GEA_MTH_VECTOR_ERR_QUAT_H__
#define __GEA_MTH_VECTOR_ERR_QUAT_H__

// mth includes
#include <gea/mth_core/error/err_base.h>
#include <gea/mth_vector/quaternion.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm_one(const quaternion &q);
inline const float norm_two(const quaternion &q);
inline const float norm_inf(const quaternion &q);

// error fucntions
inline const float error_absolute(const quaternion &q, const quaternion &qh);
inline const float error_relative(const quaternion &q, const quaternion &qh);

} // namespace mth //
} // namespace gea //

#include "err_quaternion.inl"

#endif // __GEA_MTH_VECTOR_ERR_QUAT_H__ //
