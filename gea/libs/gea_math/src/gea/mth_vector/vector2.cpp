
// mth includes
#include <gea/mth_vector/polar2.h>

// header include
#include "vector2.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector2                                                                   //
// ------------------------------------------------------------------------- //
// static constants
const vector2 vector2::ZERO   = vector2();
const vector2 vector2::X_AXIS = vector2(1.0f, 0.0f);
const vector2 vector2::Y_AXIS = vector2(0.0f, 1.0f);

// conversion
void vector2::from_polar(const polar2 &p) {
    //TODO implement
    assert(false && "implement");
}
void vector2::to_polar(polar2 &p) const { p.from_vector((*this)); }

} // namespace mth //
} // namespace gea //
