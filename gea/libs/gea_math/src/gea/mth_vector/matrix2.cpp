// header include
#include "matrix2.h"

// gea includes
#include <gea/mth_core/trigonometry.h>
#include <gea/mth_vector/quaternion.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //
// static constants
const matrix2 matrix2::IDENTITY = matrix2(mth::IDENTITY_INITIALIZATION);
const matrix2 matrix2::ZERO     = matrix2(mth::ZERO_INITIALIZATION);

// linear algebra
//TODO: tidy up
const matrix2 matrix2::inverse() const {
    const float det = determinant();
    l_assert_msg(approx_ne(det, 0.0f), "singular matrix!");

    const float det_inv = 1.0f / det;
    matrix2 inv(SKIP_INITIALIZATION);
    inv.m[0][0] = ( m[1][1]) * det_inv;
    inv.m[0][1] = (-m[0][1]) * det_inv;
    inv.m[1][0] = (-m[1][0]) * det_inv;
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
void matrix2::to_angle(float &out_angle) const {
    out_angle = atan2(m[1][0], m[0][0]);
}

} // namespace mth //
} // namespace gea //
