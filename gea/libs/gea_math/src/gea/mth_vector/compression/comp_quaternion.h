#ifndef __GEA_VMTH_COMP_QUATERNION_H__
#define __GEA_VMTH_COMP_QUATERNION_H__

// mth includes
#include <gea/mth_vector/quaternion.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// quaternion compression structs                                            //
// ------------------------------------------------------------------------- //
struct quaternion_c32 {
    uint32_t bits;
};
struct quaternion_c64 {
    uint64_t bits;
};
typedef quaternion_c32 quat_c32;
typedef quaternion_c64 quat_c64;

// ------------------------------------------------------------------------- //
// smalles three encode                                                      //
// ------------------------------------------------------------------------- //
void encode_s3(const quaternion &q, quaternion_c32 &eq);
void decode_s3(const quaternion_c32 &eq, quaternion &q);

// ------------------------------------------------------------------------- //
// polar                                                                     //
// ------------------------------------------------------------------------- //
// note: Implementation of Mark Zarb-Adami's algorithm as published in Game  //
//       Programming Gems 3.                                                 //
// ------------------------------------------------------------------------- //
void encode_polar(const quaternion &q, quaternion_c32 &cq);
void decode_polar(const quaternion_c32 &cq, quaternion &q);

// ------------------------------------------------------------------------- //
// polar adaptive                                                            //
// ------------------------------------------------------------------------- //
// note: Implementation of Mark Zarb-Adami's algorithm as published in Game  //
//       Programming Gems 3.                                                 //
// ------------------------------------------------------------------------- //
void encode_polar_adaptive(const quaternion &q, quaternion_c32 &cq);
void decode_polar_adaptive(const quaternion_c32 &cq, quaternion &q);

} // namespace mth //
} // namespace gea //

#endif // __GEA_VMTH_COMP_QUATERNION_H__ //
