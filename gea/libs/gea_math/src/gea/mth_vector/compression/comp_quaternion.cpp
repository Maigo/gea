// header include
#include "comp_quaternion.h"

// gea includes
#include <gea/mth_vector/polar3.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// smalles three encode                                                      //
// ------------------------------------------------------------------------- //
void encode_s3(const quaternion &q, quaternion_c32 &out_cq) {
    // identify smallest three
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z, ww = q.w * q.w;

    // find smallest three, store largest component in xx
    uint32_t       lc = 0;            // lc = 0b00 -> x
    if (yy > xx) { lc = 1; xx = yy; } // lc = 0b01 -> y
    if (zz > xx) { lc = 2; xx = zz; } // lc = 0b10 -> z
    if (ww > xx) { lc = 3;          } // lc = 0b11 -> w

    // smallest component and cX which will be omitted in the encoding
    float c1, c2, c3, cX;

    switch (lc) {
    case 0: cX = q.x; c1 = q.y; c2 = q.z; c3 = q.w; break; // x
    case 1: c1 = q.x; cX = q.y; c2 = q.z; c3 = q.w; break; // y
    case 2: c1 = q.x; c2 = q.y; cX = q.z; c3 = q.w; break; // z
    case 3: c1 = q.x; c2 = q.y; c3 = q.z; cX = q.w; break; // w
    default:                                        break;
    }

    // ensure omitted component is positive
    if (cX < 0) { c1 = -c1; c2 = -c2; c3 = -c3; }

    // encode - through range adaption and quantization
    // note: the smallest three components are guaranteed to be within
    // the range [-1/sqrt(2),1/sqrt(2)]. this is used to further precition.
                                                // SQRT_2 = 2 * SQRT_2_INV
    uint32_t i1 = (uint32_t) (((c1 + SQRT_2_INV) / SQRT_2) * ((1 << 10) - 1));
    uint32_t i2 = (uint32_t) (((c2 + SQRT_2_INV) / SQRT_2) * ((1 << 10) - 1));
    uint32_t i3 = (uint32_t) (((c3 + SQRT_2_INV) / SQRT_2) * ((1 << 10) - 1));

    out_cq.bits = ((0x003 & lc) << 30) |
                  ((0x3FF & i3) << 20) |
                  ((0x3FF & i2) << 10) |
                  ((0x3FF & i1) << 00);
}
void decode_s3(const quaternion_c32 &cq, quaternion &out_q) {
    // decode
    uint32_t lc = 0x003 & (cq.bits >> 30);
    uint32_t i3 = 0x3FF & (cq.bits >> 20);
    uint32_t i2 = 0x3FF & (cq.bits >> 10);
    uint32_t i1 = 0x3FF & (cq.bits >> 00);
                                            // SQRT_2 = 2 * SQRT_2_INV
    float c1 = (((float) i1 / ((1 << 10) - 1)) * SQRT_2) - SQRT_2_INV;
    float c2 = (((float) i2 / ((1 << 10) - 1)) * SQRT_2) - SQRT_2_INV;
    float c3 = (((float) i3 / ((1 << 10) - 1)) * SQRT_2) - SQRT_2_INV;

    // restore largest component
    float c0 = sqrtf(1.0f - c1 * c1 - c2 * c2 - c3 * c3);

    switch (lc) {
    case 0: out_q.x = c0; out_q.y = c1; out_q.z = c2; out_q.w = c3; break;
    case 1: out_q.x = c1; out_q.y = c0; out_q.z = c2; out_q.w = c3; break;
    case 2: out_q.x = c1; out_q.y = c2; out_q.z = c0; out_q.w = c3; break;
    case 3: out_q.x = c1; out_q.y = c2; out_q.z = c3; out_q.w = c0; break;
    default:                                                        break;
    }
}

// ------------------------------------------------------------------------- //
// polar                                                                     //
// ------------------------------------------------------------------------- //
void encode_polar(const quaternion &q, quaternion_c32 &out_cq) {
    static const float SCALE_PIo2 = PI / 2.0f;

    // get rotation axis
    float angle;
    vector3 v(SKIP_INITIALIZATION);
    q.to_axis(angle, v);

    // fold to one quadrant
    uint32_t mm = 0x0;
    if (v.x < 0.0f) { mm |= 0x4; v.x = -v.x; }
    if (v.y < 0.0f) { mm |= 0x2; v.y = -v.y; }
    if (v.z < 0.0f) { mm |= 0x1; v.z = -v.z; }

    // convert to spherical representation
    polar3 p(v);

    uint32_t i1, i2, i3;

    i1 = (uint32_t) ((p.theta / SCALE_PIo2) * ((1 <<  9) - 1));
    i2 = (uint32_t) ((p.phi   / SCALE_PIo2) * ((1 <<  9) - 1));
    i3 = (uint32_t) (sqrt(1.0f - q.w)       * ((1 << 11) - 1));

    out_cq.bits = ((0x007 & mm) << 29) |
                  ((0x1FF & i1) << 20) |
                  ((0x1FF & i2) << 11) |
                  ((0x7FF & i3) << 00);
}
void decode_polar(const quaternion_c32 &cq, quaternion &out_q) {
    static const float SCALE_PIo2 = PI / 2.0f;

    // decode
    uint32_t mm, i1, i2, i3;

    mm = ((cq.bits >> 29) & 0x007);
    i1 = ((cq.bits >> 20) & 0x1FF);
    i2 = ((cq.bits >> 11) & 0x1FF);
    i3 = ((cq.bits >> 00) & 0x7FF);

    float c1, c2, c3;
    c1 = ((float) i1 / ((1 <<  9) - 1)) * SCALE_PIo2;
    c2 = ((float) i2 / ((1 <<  9) - 1)) * SCALE_PIo2;
    c3 = ((float) i3 / ((1 << 11) - 1));

    // convert from spherical representation
    vector3 v(polar3(1.0f, c1, c2));
    float w = 1.0f - c3 * c3;

    // restore vector length
    l_assert_msg(!v.is_zero(), "zero vector!");
    float r = sqrtf((1.0f - w * w) / (v.x * v.x + v.y * v.y + v.z * v.z));

    if (mm & 0x04) v.x = -v.x;
    if (mm & 0x02) v.y = -v.y;
    if (mm & 0x01) v.z = -v.z;

    out_q.x = r * v.x, out_q.y = r * v.y, out_q.z = r * v.z, out_q.w = w;
}

// ------------------------------------------------------------------------- //
// polar adaptive                                                            //
// ------------------------------------------------------------------------- //
void encode_polar_adaptive(const quaternion &q, quaternion_c32 &out_cq) {
    static const float SCALE_PIo2_INV = 2.0f / PI;

    // get rotation axis
    float angle;
    vector3 v(SKIP_INITIALIZATION);
    q.to_axis(angle, v);

    // fold to one quadrant
    uint32_t mm = 0x0;
    if (v.x < 0.0f) { mm |= 0x4; v.x = -v.x; }
    if (v.y < 0.0f) { mm |= 0x2; v.y = -v.y; }
    if (v.z < 0.0f) { mm |= 0x1; v.z = -v.z; }

    // convert to spherical representation
    polar3 p(v);

    // adaptive encode: col = f(row)
    uint32_t row = (uint32_t) ((p.theta * SCALE_PIo2_INV) * ((1 <<  9) - 1));
    uint32_t col = (uint32_t) ((p.phi   * SCALE_PIo2_INV) * ((2 * row) + 1));

    uint32_t i1, i2; 
    i1 = row * row + col;
    i2 = (uint32_t) (sqrt(1.0f - q.w) * ((1 << 11) - 1));

    out_cq.bits = ((0x00007 & mm) << 29) |
                  ((0x3FFFF & i1) << 11) |
                  ((0x007FF & i2) << 00);
}
void decode_polar_adaptive(const quaternion_c32 &cq, quaternion &out_q) {
    static const float SCALE_PIo2 = PI / 2.0f;

    // adaptive decode
    uint32_t mm, i1, i2;
    mm = ((cq.bits >> 29) & 0x00007);
    i1 = ((cq.bits >> 11) & 0x3FFFF);
    i2 = ((cq.bits >> 00) & 0x007FF);

    uint32_t row = (uint32_t) sqrtf((float) i1);
    uint32_t col = i1 - row * row;

    float c1, c2, c3;
    c1 = ((float) row / ((1 <<  9) - 1)) * SCALE_PIo2;
    c2 = ((float) col / ((2 * row) + 1)) * SCALE_PIo2;
    c3 = ((float) i2  / ((1 << 11) - 1));

    // convert from spherical representation
    vector3 v(polar3(1.0f, c1, c2));
    float w = 1.0f - c3 * c3;

    // unfold to entire sphere
    if (mm & 0x04) v.x = -v.x;
    if (mm & 0x02) v.y = -v.y;
    if (mm & 0x01) v.z = -v.z;

    // restore vector length
    l_assert_msg(!v.is_zero(), "zero vector!");
    float r = sqrtf((1.0f - w * w) / (v.x * v.x + v.y * v.y + v.z * v.z));

    out_q.x = r * v.x, out_q.y = r * v.y, out_q.z = r * v.z, out_q.w = w;
}

} // namespace mth //
} // namespace gea //
