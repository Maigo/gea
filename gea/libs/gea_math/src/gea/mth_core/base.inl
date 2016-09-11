
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
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const float f0, const float f1, const float e) { return (fabs(f0 - f1) <= e); }
inline const bool approx_ne(const float f0, const float f1, const float e) { return (fabs(f0 - f1)  > e); }

inline const bool approx_leq(const float f0, const float f1, const float e) { return (f0 < (f1 + e)); }
inline const bool approx_geq(const float f0, const float f1, const float e) { return (f0 > (f1 - e)); }

// approximative scalar
inline const float upb(const float f, const float e) { return (f + e); }
inline const float lwb(const float f, const float e) { return (f - e); }

// nice scalar
inline const bool nice(const float number) { return _finite(number) && !_isnan(number); }

// finite scalar
inline const bool finite(const float number) { return _finite(number) != 0; }

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

} // namespace mth //
} // namespace gea //
