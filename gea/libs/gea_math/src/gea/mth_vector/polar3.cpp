
// mth includes
#include <gea/mth_vector/vector3.h>

// header include
#include "polar3.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polar3                                                                     //
// ------------------------------------------------------------------------- //
// conversion
void polar3::from_vector(const vector3 &v) {
    r = v.length();
    if (r != 0.0f) {
        theta = acosf(mth::clamp(v.z/r, -1.0f, 1.0f));
        phi   = atan2f(v.y, v.x);
    } else {
        theta = phi = 0.0f;
    }
}
void polar3::to_vector(vector3 &v) const {
    v.from_polar((*this));
}

} // namespace mth //
} // namespace gea //
