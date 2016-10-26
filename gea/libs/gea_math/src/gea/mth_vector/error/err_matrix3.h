#ifndef __GEA_MTH_VECTOR_ERR_MATRIX3_H__
#define __GEA_MTH_VECTOR_ERR_MATRIX3_H__

// gea includes
#include <gea/mth_core/error/err_base.h>
#include <gea/mth_vector/matrix3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm_one(const matrix3 &m);
inline const float norm_two(const matrix3 &m);
inline const float norm_inf(const matrix3 &m);

inline const float norm_1(const matrix3 &m);
inline const float norm_inf(const matrix3 &m);

// error functions

} // namespace mth //
} // namespace gea //

#include "err_matrix3.inl"

#endif // __GEA_MTH_VECTOR_ERR_MATRIX3_H__ //
