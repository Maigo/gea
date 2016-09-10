#ifndef __GEA_VMTH_COMP_VECTOR3_H__
#define __GEA_VMTH_COMP_VECTOR3_H__

// stl includes
#include <assert.h>

// mth includes
#include <gea/mth_vector/vector3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector3 compression structs                                               //
// ------------------------------------------------------------------------- //
struct vector3_c48 {
    uint16_t bits[3];
};

// ------------------------------------------------------------------------- //
// half precision encoding                                                   //
// ------------------------------------------------------------------------- //
void encode_half(const vector3 &v, vector3_c48 &out_cv);
void decode_half(const vector3_c48 &cv, vector3 &out_v);

// ------------------------------------------------------------------------- //
// fix precision encoding                                                    //
// ------------------------------------------------------------------------- //
namespace fix {

struct default_range {
    static inline const float min(); // -1000.0f
    static inline const float max(); //  1000.0f
};

} // namespace fix //

template <typename RANGE>
void encode_fix(const vector3 &v, vector3_c48 &out_cv);
template <typename RANGE>
void decode_fix(const vector3_c48 &cv, vector3 &out_v);

} // namespace mth //
} // namespace gea //

#include "comp_vector3.inl"

#endif // __GEA_VMTH_COMP_VECTOR3_H__ //
