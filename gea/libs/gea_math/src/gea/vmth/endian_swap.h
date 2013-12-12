#ifndef __GEA_VMTH_ENDIAN_SWAP_H__
#define __GEA_VMTH_ENDIAN_SWAP_H__

// mth includes
#include <gea/bmth/endian_swap.h>
#include <gea/vmth/matrix3.h>
#include <gea/vmth/polar.h>
#include <gea/vmth/quaternion.h>
#include <gea/vmth/vector3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<matrix3>(matrix3 &m);

// ------------------------------------------------------------------------- //
// polar                                                                     //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<polar>(polar &p);

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<quaternion>(quaternion &q);

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<vector3>(vector3 &v);

} // namespace mth //
} // namespace gea //

#include "endian_swap.inl"

#endif // __GEA_VMTH_ENDIAN_SWAP_H__ //
