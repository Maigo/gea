#ifndef __GEA_BMTH_ERR_BASE_H__
#define __GEA_BMTH_ERR_BASE_H__

// mth includes
#include <gea/bmth/base.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// base                                                                      //
// ------------------------------------------------------------------------- //
// norm functions
inline float norm(const float &f);

// error functions
inline float error_absolute(const float &f, const float &fh);
inline float error_relative(const float &f, const float &fh);

} // namespace mth //
} // namespace gea //

#include "err_base.inl"

#endif // __GEA_BMTH_ERR_BASE_H__ //
