// header include
#include "polar2.h"

// gea includes
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polar2                                                                     //
// ------------------------------------------------------------------------- //
// conversion
void polar2::from_vector(const vector2 &v) {
    r = v.length();
    theta = (r != 0.0f) ? (float(M_PI) + atan2f(v.y, v.x)) : 0.0f;
}
void polar2::to_vector(vector2 &out_v) const {
    out_v.from_polar((*this));
}

} // namespace mth //
} // namespace gea //
