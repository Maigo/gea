
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
void encode_fix(const vector3 &v, vector3_c48 &cv) {
    // assert valid parameters
    assert((RANGE::min() < RANGE::max()) && "invalid parameters!");
    // assert vector is encodable
    assert(mth::range(v.x, RANGE::min(), RANGE::max()) &&
           mth::range(v.y, RANGE::min(), RANGE::max()) &&
           mth::range(v.z, RANGE::min(), RANGE::max()) && "out of bounds!");

    static const float enc_max       = std::numeric_limits<uint16_t>::max();
    static const float enc_range_inv = 1.0f / (RANGE::max() - RANGE::min());

    float x = ((float) enc_max) * ((v.x - RANGE::min()) * enc_range_inv);
    cv.bits[0] = (uint16_t) mth::clamp(x, 0.0f, enc_max);

    float y = ((float) enc_max) * ((v.y - RANGE::min()) * enc_range_inv);
    cv.bits[1] = (uint16_t) mth::clamp(y, 0.0f, enc_max);

    float z = ((float) enc_max) * ((v.z - RANGE::min()) * enc_range_inv);
    cv.bits[2] = (uint16_t) mth::clamp(z, 0.0f, enc_max);
}
template <typename RANGE>
void decode_fix(const vector3_c48 &cv, vector3 &v) {
    static const float enc_max_inv = 1.0f / std::numeric_limits<uint16_t>::max();
    static const float enc_range   = RANGE::max() - RANGE::min();

    v.x = ( (cv.bits[0] * enc_max_inv) * enc_range) + RANGE::min();
    v.y = ( (cv.bits[1] * enc_max_inv) * enc_range) + RANGE::min();
    v.z = ( (cv.bits[2] * enc_max_inv) * enc_range) + RANGE::min();
}

} // namespace mth //
} // namespace gea //
