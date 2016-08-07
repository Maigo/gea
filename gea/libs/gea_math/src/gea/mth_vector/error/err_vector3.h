#ifndef __GEA_VMTH_ERR_VECTOR3_H__
#define __GEA_VMTH_ERR_VECTOR3_H__

// mth includes
#include <gea/bmth/error/err_base.h>
#include <gea/vmth/vector3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm_one(const vector3 &v);
inline const float norm_two(const vector3 &v);
inline const float norm_inf(const vector3 &v);

// error fucntions
inline const float error_absolute(const vector3 &v, const vector3 &vh);
inline const float error_relative(const vector3 &v, const vector3 &vh);

} // namespace mth //
} // namespace gea //

#include "err_vector3.inl"

#endif // __GEA_VMTH_ERR_VECTOR3_H__ //
