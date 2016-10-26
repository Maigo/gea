#ifndef __GEA_MTH_VECTOR_ENDIAN_SWAP_H__
#define __GEA_MTH_VECTOR_ENDIAN_SWAP_H__

// gea includes
#include <gea/mth_core/endian_swap.h>
#include <gea/mth_vector/matrix3.h>
#include <gea/mth_vector/polar3.h>
#include <gea/mth_vector/quaternion.h>
#include <gea/mth_vector/vector3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<matrix3>(matrix3 &out_m);

// ------------------------------------------------------------------------- //
// polar                                                                     //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<polar3>(polar3 &out_p);

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<quaternion>(quaternion &out_q);

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<vector3>(vector3 &out_v);

} // namespace mth //
} // namespace gea //

#include "endian_swap.inl"

#endif // __GEA_MTH_VECTOR_ENDIAN_SWAP_H__ //
