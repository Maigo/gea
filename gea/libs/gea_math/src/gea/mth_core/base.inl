
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //
// conversion functions
inline const float degrees_to_radians(float deg) { return deg * PI / 180.0f; }
inline const float radians_to_degrees(float rad) { return rad * 180.0f / PI; }

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(float f1, float f2, float e) { return (fabs(f1-f2) <= e); }
inline bool approx_ne(float f1, float f2, float e) { return (fabs(f1-f2)  > e); }

// approximative scalar
inline float upb(float f, float e) { return (f+e); }
inline float lwb(float f, float e) { return (f-e); }

// nice scalar
inline bool nice(float number) { return _finite(number) && !_isnan(number); }
// finite scalar
inline bool finite(float number) { return _finite(number) != 0; }
// optimized sin & cos method
inline void fsincos(float angle, float &sin, float &cos) {
    return i_fsincos(angle, sin, cos);
}

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
template <typename T> inline bool range(const T &t, const T &min, const T &max) {
    return min <= t && t <= max;
}

} // namespace mth //
} // namespace gea //
