// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// fix precision encoding                                                    //
// ------------------------------------------------------------------------- //
namespace fix {

inline const float default_range::min() { return -1000.0f; }
inline const float default_range::max() { return  1000.0f; }

} // namespace fix //

template <typename RANGE>
void encode_fix(const vector3 &v, vector3_c48 &out_cv) {
    // assert valid parameters
    c_assert_msg(RANGE::min() < RANGE::max(), "invalid parameters!");
    // assert vector is encodable
    l_assert_msg(mth::range(v.x, RANGE::min(), RANGE::max()) &&
                 mth::range(v.y, RANGE::min(), RANGE::max()) &&
                 mth::range(v.z, RANGE::min(), RANGE::max()),
                 "out of bounds!");

    static const float enc_max       = std::numeric_limits<uint16_t>::max();
    static const float enc_range_inv = 1.0f / (RANGE::max() - RANGE::min());

    float x = ((float) enc_max) * ((v.x - RANGE::min()) * enc_range_inv);
    out_cv.bits[0] = (uint16_t) mth::clamp(x, 0.0f, enc_max);

    float y = ((float) enc_max) * ((v.y - RANGE::min()) * enc_range_inv);
    out_cv.bits[1] = (uint16_t) mth::clamp(y, 0.0f, enc_max);

    float z = ((float) enc_max) * ((v.z - RANGE::min()) * enc_range_inv);
    out_cv.bits[2] = (uint16_t) mth::clamp(z, 0.0f, enc_max);
}
template <typename RANGE>
void decode_fix(const vector3_c48 &cv, vector3 &out_v) {
    static const float enc_max_inv = 1.0f / std::numeric_limits<uint16_t>::max();
    static const float enc_range   = RANGE::max() - RANGE::min();

    out_v.x = ( (cv.bits[0] * enc_max_inv) * enc_range) + RANGE::min();
    out_v.y = ( (cv.bits[1] * enc_max_inv) * enc_range) + RANGE::min();
    out_v.z = ( (cv.bits[2] * enc_max_inv) * enc_range) + RANGE::min();
}

} // namespace mth //
} // namespace gea //
