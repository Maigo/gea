// std includes
#include <math.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //
// conversion functions
inline const float degrees_to_radians(const float degrees) { return degrees * float(M_PI) / 180.0f; }
inline const float radians_to_degrees(const float radians) { return radians * 180.0f / float(M_PI); }

// optimized sin & cos method
inline void fsincos(const float angle, float &out_sin, float &out_cos) {
    return i_fsincos(angle, out_sin, out_cos);
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_angle_eq(const float a0, const float a1, const float e) {
    return fabs(fmod(fabs(a0 - a1) + float(M_PI), 2.0f * float(M_PI)) - float(M_PI)) <= e;
}
inline const bool approx_angle_ne(const float a0, const float a1, const float e) {
    return fabs(fmod(fabs(a0 - a1) + float(M_PI), 2.0f * float(M_PI)) - float(M_PI)) > e;
}

} // namespace mth //
} // namespace gea //
