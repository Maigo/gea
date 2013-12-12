
// mth includes
#include <gea/vmth/polar3.h>

// header include
#include "vector3.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
// static constants
const vector3 vector3::ZERO   = vector3();
const vector3 vector3::X_AXIS = vector3(1.0f, 0.0f, 0.0f);
const vector3 vector3::Y_AXIS = vector3(0.0f, 1.0f, 0.0f);
const vector3 vector3::Z_AXIS = vector3(0.0f, 0.0f, 1.0f);

// conversion
void vector3::from_polar(const polar3 &p) {
    float sin_theta, cos_theta, sin_phi, cos_phi;
    fsincos(p.theta, sin_theta, cos_theta);
    fsincos(p.phi,   sin_phi,   cos_phi);

    x = p.r * sin_theta * cos_phi;
    y = p.r * sin_theta * sin_phi;
    z = p.r * cos_theta;
}
void vector3::to_polar(polar3 &p) const { p.from_vector((*this)); }

} // namespace mth //
} // namespace gea //
