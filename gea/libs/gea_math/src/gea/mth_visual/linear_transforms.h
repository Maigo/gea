#pragma once

namespace gea {
namespace mth {

// foraward declarations
class vector3;
class matrix4;

// ------------------------------------------------------------------------- //
// linear_transforms                                                         //
// ------------------------------------------------------------------------- //

inline void rotation_matrix(const float angle, const vector3 &axis, matrix4 &out_m);
inline void translation_matrix(const vector3 &translation, matrix4 &out_m);
inline void orthogonal_matrix(const float left, const float right, const float bottom, const float top, const float n, const float f, matrix4 &out_m);
inline void perspective_matrix(const float y_fov, const float aspect, const float n, const float f, matrix4 &out_m);

} // namespace mth //
} // namespace gea //

#include "linear_transforms.inl"
