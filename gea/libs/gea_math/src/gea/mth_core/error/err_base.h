#ifndef __GEA_MTH_CORE_ERR_BASE_H__
#define __GEA_MTH_CORE_ERR_BASE_H__

// mth includes
#include <gea/mth_core/base.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// base                                                                      //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm(const float &f);

// error functions
inline const float error_absolute(const float &f, const float &fh);
inline const float error_relative(const float &f, const float &fh);

} // namespace mth //
} // namespace gea //

#include "err_base.inl"

#endif // __GEA_MTH_CORE_ERR_BASE_H__ //
