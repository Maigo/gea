// header include
#include "quaternion.h"

// gea includes
#include <gea/mth_core/trigonometry.h>
#include <gea/mth_vector/matrix3.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
// static constants
const quaternion quaternion::ZERO     = quaternion(mth::ZERO_INITIALIZATION);
const quaternion quaternion::IDENTITY = quaternion(mth::IDENTITY_INITIALIZATION);

// conversion
void quaternion::from_axis(const float angle, const vector3 &axis) {
    float sin, cos;
    fsincos(angle / 2.0f, sin, cos);
    x = axis.x * sin;
    y = axis.y * sin;
    z = axis.z * sin;
    w = cos;
}
void quaternion::to_axis(float &out_angle, vector3 &out_axis) const {
    const float s = sqrtf(1.0f - w*w);
    out_angle = 2.0f * acosf(w);

    if (!approx_eq(s, 0.0f)) {
        const float inv = 1.0f / s;
        out_axis.x = x * inv;
        out_axis.y = y * inv;
        out_axis.z = z * inv;
    } else {
        out_axis.x = x;
        out_axis.y = y;
        out_axis.z = z;
    }
}
//note: euler conversion math based on notes from
// http://www.euclideanspace.com/maths/geometry/rotations/euler/index.htm
void quaternion::from_euler(const float heading, const float attitude, const float bank) {
    float sin_heading, cos_heading, sin_attitude, cos_attitude, sin_bank, cos_bank;
    fsincos(heading / 2.0f,  sin_heading,  cos_heading);
    fsincos(attitude / 2.0f, sin_attitude, cos_attitude);
    fsincos(bank / 2.0f,     sin_bank,     cos_bank);

    x = cos_heading * cos_attitude * sin_bank + sin_heading * sin_attitude * cos_bank;
    y = sin_heading * cos_attitude * cos_bank + cos_heading * sin_attitude * sin_bank;
    z = cos_heading * sin_attitude * cos_bank - sin_heading * cos_attitude * sin_bank;
    w = cos_heading * cos_attitude * cos_bank - sin_heading * sin_attitude * sin_bank;
}
void quaternion::to_euler(float &out_heading, float &out_attitude, float &out_bank) const {
    l_assert_msg(approx_eq(length(), 1.0f), "non-normalised quaternion!");

    //TODO: tidy up
    float test = x * y + z * w;
    if (test > mth::lwb(0.5f)) { // singularity at north pole
        out_heading  = 2.0f * atan2f(x, w);
        out_attitude = PI / 2.0f;
        out_bank     = 0;
    } else if (test < mth::upb(-0.5f)) { // singularity at south pole
        out_heading  = -2.0f * atan2f(x, w);
        out_attitude = -PI / 2.0f;
        out_bank     = 0;
    } else {
        out_heading  = atan2f(2.0f * y * w - 2.0f * x * z, 1.0f - 2.0f * y * y - 2.0f * z * z);
        out_attitude = asinf(2.0f * test);
        out_bank     = atan2f(2.0f * x * w - 2.0f * y * z, 1.0f - 2.0f * x * x - 2 * z * z);
    }
}

void quaternion::from_matrix(const matrix3 &m) {
    // dynamic construction (based on trace) to minimize error propagation
    const float tr = m.trace() + 1.0f;

    float tr_sqrt, tr_sqrt_inv;
    int32_t i1, i2, i3;
    if (tr >= 1.0f) { 
        tr_sqrt = sqrtf(tr) * 2.0f;     // tr_sqrt = 4 * q.w 
        tr_sqrt_inv = 1.0f / tr_sqrt;
        x = (m(2,1) - m(1,2)) * tr_sqrt_inv;
        y = (m(0,2) - m(2,0)) * tr_sqrt_inv;
        z = (m(1,0) - m(0,1)) * tr_sqrt_inv;
        w =  0.25f * tr_sqrt;
    } else {
        // determine largest component
        // set indicies according to matrix
        i1 = mth::lrgst(m(0, 0), m(1, 1), m(2, 2)); // i1   |0|1|2|
        i2 = (i1 + 1) % 3;                          // i2 = |1|2|0|
        i3 = (i2 + 1) % 3;                          // i3   |2|0|1| 

        tr_sqrt = sqrtf(1.0f + m(i1, i1) - m(i2, i2) - m(i3, i3)) * 2.0f;
        tr_sqrt_inv = 1.0f / tr_sqrt;

        // construct quaternion
        (*this)[i1] = 0.25f * tr_sqrt;
        (*this)[i2] = (m(i2, i1) + m(i1, i2)) * tr_sqrt_inv;
        (*this)[i3] = (m(i3, i1) + m(i1, i3)) * tr_sqrt_inv;
        (*this)[3] =  (m(i3, i2) - m(i2, i3)) * tr_sqrt_inv;  // q.w
    }
}
void quaternion::to_matrix(matrix3 &out_m) const {
    out_m.from_quaternion((*this));
}

} // namespace mth //
} // namespace gea //
