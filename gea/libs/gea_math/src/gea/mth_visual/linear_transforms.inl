#pragma once

// header include
#include "linear_transforms.h"

// gea includes
#include <gea/mth_core/base.h>
#include <gea/mth_core/trigonometry.h>
#include <gea/mth_vector/vector3.h>
#include <gea/mth_vector/matrix4.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// linear_transforms                                                         //
// ------------------------------------------------------------------------- //

void rotation_matrix(const float angle, const vector3& axis, matrix4& out_m)
{
    float sin_angle, cos_angle;
    fsincos(angle, sin_angle, cos_angle);

    const vector3 axis2 = axis * axis;
    const float l2 = (axis2.x * axis2.x) + (axis2.y * axis2.y) + (axis2.z * axis2.z);
    const float l2_sqrt = sqrtf(l2);

    if (approx_ne(l2, 0.f)) {
        out_m.m[0][0] = (axis2.x + (axis2.y + axis2.z) * cos_angle) / l2;
        out_m.m[0][1] = (axis.x * axis.y * (1 - cos_angle) - axis.z * l2_sqrt * sin_angle) / l2;
        out_m.m[0][2] = (axis.x * axis.z * (1 - cos_angle) + axis.y * l2_sqrt * sin_angle) / l2;
        out_m.m[0][3] = 0.0f;

        out_m.m[1][0] = (axis.x * axis.y * (1 - cos_angle) + axis.z * l2_sqrt * sin_angle) / l2;
        out_m.m[1][1] = (axis2.y + (axis2.x + axis2.z) * cos_angle) / l2;
        out_m.m[1][2] = (axis.y * axis.z * (1 - cos_angle) - axis.x * l2_sqrt * sin_angle) / l2;
        out_m.m[1][3] = 0.0f;

        out_m.m[2][0] = (axis.x * axis.z * (1 - cos_angle) - axis.y * l2_sqrt * sin_angle) / l2;
        out_m.m[2][1] = (axis.y * axis.z * (1 - cos_angle) + axis.x * l2_sqrt * sin_angle) / l2;
        out_m.m[2][2] = (axis2.z + (axis2.x + axis2.y) * cos_angle) / l2;
        out_m.m[2][3] = 0.0f;

        out_m.m[3][0] = 0.0f;
        out_m.m[3][1] = 0.0f;
        out_m.m[3][2] = 0.0f;
        out_m.m[3][3] = 1.0f;

    }
    else {
        out_m = matrix4(mth::IDENTITY_INITIALIZATION);
    }
}

void translation_matrix(const vector3& translation, matrix4& out_m)
{
    out_m = matrix4(mth::IDENTITY_INITIALIZATION);
    out_m.m[2][0] = translation.x;
    out_m.m[2][1] = translation.y;
    out_m.m[2][2] = translation.z;
}

void orthogonal_matrix(const float left, const float right, const float bottom, const float top, const float n, const float f, matrix4& out_m)
{
    out_m = matrix4(mth::IDENTITY_INITIALIZATION);
    out_m.m[0][0] = 2.0f / (right - left);
    out_m.m[1][1] = 2.0f / (top - bottom);
    out_m.m[2][2] = -2.0f / (f - n);
    out_m.m[3][0] = -(right + left) / (right - left);
    out_m.m[3][1] = -(top + bottom) / (top - bottom);
    out_m.m[3][2] = -(f + n) / (f - n);
}

void perspective_matrix(const float y_fov, const float aspect, const float n, const float f, matrix4& out_m)
{
    const float y_cot = 1.0f / tanf(y_fov * float(M_PI) / 360.0f);

    out_m = matrix4(mth::IDENTITY_INITIALIZATION);
    out_m.m[0][0] = y_cot / aspect;
    out_m.m[1][1] = y_cot;
    out_m.m[2][2] = (n + f) / (n - f);
    out_m.m[2][3] = -1.0f;
    out_m.m[3][2] = 2.0f * n * f / (n - f);
    out_m.m[3][3] = 0.0f;
}

} // namespace mth //
} // namespace gea //
