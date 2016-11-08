// std includes
#include <math.h>
#include <type_traits>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //
// conversion functions
inline const float degrees_to_radians(const float deg) { return deg * PI / 180.0f; }
inline const float radians_to_degrees(const float rad) { return rad * 180.0f / PI; }

// optimized sin & cos method
inline void fsincos(const float angle, float &out_sin, float &out_cos) {
    return i_fsincos(angle, out_sin, out_cos);
}

// ------------------------------------------------------------------------- //
// arithmetic functions                                                      //
// ------------------------------------------------------------------------- //
// modulo
inline const float arithmetic_mod(const float value, const float mod)
{
    float value_mod = fmod(value, mod);
    return (value_mod < 0.0) ? value_mod + mod : value_mod;
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const float f0, const float f1, const float e) { return (fabs(f0 - f1) <= e); }
inline const bool approx_ne(const float f0, const float f1, const float e) { return (fabs(f0 - f1)  > e); }

inline const bool approx_ls(const float f0, const float f1, const float e) { return (f0 < (f1 - e)); }
inline const bool approx_gt(const float f0, const float f1, const float e) { return (f0 > (f1 + e)); }

inline const bool approx_leq(const float f0, const float f1, const float e) { return (f0 < (f1 + e)); }
inline const bool approx_geq(const float f0, const float f1, const float e) { return (f0 > (f1 - e)); }

// approximative scalar
inline const float upb(const float f, const float e) { return (f + e); }
inline const float lwb(const float f, const float e) { return (f - e); }

// attributes
inline const bool nice(const float number) { return _finite(number) && !_isnan(number); }
inline const bool finite(const float number) { return _finite(number) != 0; }

// round
template <> inline const double round(const double v) { return ::round(v); }
template <> inline const double ceil(const double v) { return ::ceil(v); }
template <> inline const double floor(const double v) { return ::floor(v); }
template <> inline const float round(const float v) { return ::roundf(v); }
template <> inline const float ceil(const float v) { return ::ceilf(v); }
template <> inline const float floor(const float v) { return ::floorf(v); }

// ------------------------------------------------------------------------- //
// Template Functions                                                        //
// ------------------------------------------------------------------------- //
// max / min
template <typename T> inline const T min(const T &a, const T &b) { return (a > b ? b : a); }
template <typename T> inline const T min(const T &a, const T &b, const T &c) { return (a > b ? (b > c ? c : b) : a); }
template <typename T> inline const T min(const T &a, const T &b, const T &c, const T &d) { return (a > b ? (b > c ? (c > d ? d : c) : b) : a); }
template <typename T> inline const T max(const T &a, const T &b) { return (a < b ? b : a); }
template <typename T> inline const T max(const T &a, const T &b, const T &c) { return (a < b ? (b < c ? c : b) : a); }
template <typename T> inline const T max(const T &a, const T &b, const T &c, const T &d) { return (a < b ? (b < c ? (c < d ? d : c) : b) : a); }

// smallest / largest
template <typename T>
inline const uint32_t smlst(const T &a, const T &b) { return (a > b ? 1 : 0); }
template <typename T>
inline const uint32_t smlst(const T &a, const T &b, const T &c) { return (a > b ? (b > c ? 2 : 1) : 0); }
template <typename T>
inline const uint32_t lrgst(const T &a, const T &b) { return (a < b ? 1 : 0); }
template <typename T>
inline const uint32_t lrgst(const T &a, const T &b, const T &c) { return (a < b ? (b < c ? 2 : 1) : 0); }

// clamp
template <typename T>
inline const T clamp(const T &t, const T &min, const T &max) {
    return mth::max(min, mth::min(max, t));
}

// range
template <typename T> inline const bool range(const T &t, const T &min, const T &max) {
    return min <= t && t <= max;
}

// sign
namespace internal {
template <typename T> inline const int sign(T x, const std::false_type is_unsigned) { return T(0) < x; }
template <typename T> inline const int sign(T x, const std::true_type  is_signed) { return (T(0) < x) - (x < T(0)); }
} // namespace internal //

template <typename T> inline const int sign(const T x) { return internal::sign(x, std::is_signed<T>()); }

} // namespace mth //
} // namespace gea //
