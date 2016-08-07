
// mth includes
#include <gea/mth_core/type/half.h>

// header include
#include "comp_vector3.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// half precision encoding                                                   //
// ------------------------------------------------------------------------- //
void encode_half(const vector3 &v, vector3_c48 &cv) {
    // assert vector is encodable
    assert(half::can_pack(v.x) && half::can_pack(v.y) && half::can_pack(v.z) && "out of bounds error!");

    // encode float -> half
    cv.bits[0] = half(v.x).bits();
    cv.bits[1] = half(v.y).bits();
    cv.bits[2] = half(v.z).bits();
}
void decode_half(const vector3_c48 &cv, vector3 &v) {
    // decode half -> float
    v.x = (float) half(cv.bits[0]);
    v.y = (float) half(cv.bits[1]);
    v.z = (float) half(cv.bits[2]);
}

} // namespace mth //
} // namespace gea //
