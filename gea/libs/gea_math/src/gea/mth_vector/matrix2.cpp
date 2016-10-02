
// mth includes
#include <gea/mth_vector/quaternion.h>

// header include
#include "matrix2.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //
// static constants
const matrix2 matrix2::IDENTITY = matrix2(1.0f, 1.0f);
const matrix2 matrix2::ZERO     = matrix2();

// linear algebra
//TODO: tidy up
const matrix2 matrix2::inverse() const {
    float det = determinant();
    assert((det > 0.0f) && "singular matrix!");

    float det_inv = 1.0f / det;
    matrix2 inv(SKIP_INITIALIZATION);
    inv.m[0][0] = ( m[1][1]) * det_inv;
    inv.m[0][1] = (-m[1][0]) * det_inv;
    inv.m[1][0] = (-m[0][1]) * det_inv;
    inv.m[1][1] = ( m[0][0]) * det_inv;
    return inv;
}

// conversion
void matrix2::from_angle(const float angle) {
    float sin_angle, cos_angle;
    fsincos(angle, sin_angle, cos_angle);

    m[0][0] = cos_angle;  m[0][1] = -sin_angle;
    m[1][0] = sin_angle;  m[1][1] =  cos_angle;
}
void matrix2::to_angle(float &out_angle) {
    //TODO: implement
}

} // namespace mth //
} // namespace gea //
