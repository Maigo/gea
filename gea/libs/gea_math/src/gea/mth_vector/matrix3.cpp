// header include
#include "matrix3.h"

// gea includes 
#include <gea/mth_core/trigonometry.h>
#include <gea/mth_vector/quaternion.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
// static constants
const matrix3 matrix3::IDENTITY = matrix3(mth::IDENTITY_INITIALIZATION);
const matrix3 matrix3::ZERO     = matrix3(mth::ZERO_INITIALIZATION);

// linear algebra
//TODO: tidy up
const matrix3 matrix3::inverse() const {
    const float det = determinant();
    l_assert_msg(approx_ne(det, 0.0f), "singular matrix!");

    const float det_inv = 1.0f / det;
    matrix3 inv(SKIP_INITIALIZATION);
    inv.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * det_inv;
    inv.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * det_inv;
    inv.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * det_inv;
    inv.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * det_inv;
    inv.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * det_inv;
    inv.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * det_inv;
    inv.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * det_inv;
    inv.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * det_inv;
    inv.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * det_inv;
    return inv;
}

// conversion
//note: quaternion conversion math based on notes from
// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
void matrix3::from_quaternion(const quaternion &q) {
    //TODO: optimize
    m[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z*q.z; m[0][1] = 2.0f * q.x * q.y - 2.0f * q.z * q.w;        m[0][2] = 2.0f * q.x * q.z + 2.0f * q.y * q.w;
    m[1][0] = 2.0f * q.x * q.y + 2.0f * q.z * q.w;      m[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z; m[1][2] = 2.0f * q.y * q.z - 2.0f * q.x * q.w;
    m[2][0] = 2.0f * q.x * q.z - 2.0f * q.y * q.w;      m[2][1] = 2.0f * q.y * q.z + 2.0f * q.x * q.w;        m[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
}
void matrix3::to_quaternion(quaternion &out_q) const {
    out_q.from_matrix((*this));
}
//note: euler conversion math based on notes from
// http://www.euclideanspace.com/maths/geometry/rotations/euler/index.htm
// rotation matrix is constructed according to:
// R = ([Ry(heading)][Rz(attitude)])[Rx(bank)]
void matrix3::from_euler(const float heading, const float attitude, const float bank) {
    float sin_heading, cos_heading, sin_attitude, cos_attitude, sin_bank, cos_bank;
    fsincos(heading, sin_heading, cos_heading);
    fsincos(attitude, sin_attitude, cos_attitude);
    fsincos(bank, sin_bank, cos_bank);

    m[0][0] =  cos_heading * cos_attitude; m[0][1] = sin_heading * sin_bank - cos_heading * sin_attitude * cos_bank; m[0][2] = cos_heading * sin_attitude * sin_bank + sin_heading * cos_bank;
    m[1][0] =  sin_attitude;               m[1][1] = cos_attitude * cos_bank;                                        m[1][2] =-cos_attitude * sin_bank;
    m[2][0] = -sin_heading * cos_attitude; m[2][1] = sin_heading * sin_attitude * cos_bank + cos_heading * sin_bank; m[2][2] =-sin_heading * sin_attitude * sin_bank + cos_heading * cos_bank;
}
void matrix3::to_euler(float &out_heading, float &out_attitude, float &out_bank) const {
    // m20 in [~-1,~1]
    if ((m[1][0] > mth::upb(-1.0f)) && (m[1][0] < mth::lwb(1.0f))) {
        out_heading = atan2f(-m[2][0], m[0][0]);
        // force m10 to [-1,1]
        out_attitude = asinf(mth::clamp(m[1][0], -1.0f, 1.0f));
        out_bank = atan2f(-m[1][2], m[1][1]);
    // singularity at south or north pole
    } else {
        out_heading = atan2f(m[0][2], m[2][2]);
        out_attitude = (m[1][0] < 0.0f) ? -PI / 2.0f : PI / 2.0f;
        out_bank = 0;
    }
}

} // namespace mth //
} // namespace gea //
