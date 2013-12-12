#ifndef __GEA_BMTH_BASE_H__
#define __GEA_BMTH_BASE_H__

// std includes
#include <float.h>
#include <math.h>

// mth includes
#include <gea/bmth/intrinsic.h>

#ifndef M_E
#   define M_E          1.44269504088896340736
#endif // M_E //
#ifndef M_LOG2E
#   define M_LOG2E      0.434294481903251827651
#endif // M_LOG2E //
#ifndef M_LN2
#   define M_LN2        0.693147180559945309417
#endif // M_LN2 //
#ifndef M_LN10
#   define M_LN10       2.30258509299404568402
#endif // M_LN10 //
#ifndef M_PI
#   define M_PI         3.14159265358979323846
#endif // M_PI //
#ifndef M_PI_2
#   define M_PI_2       1.57079632679489661923
#endif // M_PI_2 //
#ifndef M_PI_4
#   define M_PI_4       0.785398163397448309616
#endif // M_PI_4 //
#ifndef M_1_PI
#   define M_1_PI       0.318309886183790671538
#endif // M_1_PI //
#ifndef M_2_PI
#   define M_2_PI       0.636619772367581343076
#endif // M_2_PI //
#ifndef M_2_SQRTPI
#   define M_2_SQRTPI   1.12837916709551257390
#endif // M_2_SQRTPI //
#ifndef M_SQRT2
#   define M_SQRT2      1.41421356237309504880
#endif // M_SQRT2 //
#ifndef M_SQRT1_2
#   define M_SQRT1_2    0.707106781186547524401
#endif // M_SQRT1_2 //

namespace gea {
namespace mth {

// ----------------------------------------------------------------------------
// global static constants
// ----------------------------------------------------------------------------
// static constants
static const float PI          = 3.1415926535897932384626433832795f;
static const float SQRT_PI     = 1.7724538509055160272981674833411f;
static const float SQRT_PI_INV = 1.0f / SQRT_PI;
static const float SQRT_2      = 1.4142135623730950488016887242097f;
static const float SQRT_2_INV  = 1.0f / SQRT_2;
static const float E           = 2.7182818284590452353602874713527f;

// omit initialization marker
enum skip_initialization { SKIP_INITIALIZATION };

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //
// conversion functions
inline const float degrees_to_radians(float deg);
inline const float radians_to_degrees(float rad);
// optimized sin & cos method
inline void fsincos(float angle, float &sin, float &cos);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
static const float APPROX_EPSILON = 1.0e-4f;
inline bool approx_eq(float f1, float f2, float e = APPROX_EPSILON);
inline bool approx_ne(float f1, float f2, float e = APPROX_EPSILON);

// approximative scalar
inline float upb(float f, float e = APPROX_EPSILON); // upper bound
inline float lwb(float f, float e = APPROX_EPSILON); // lower bound

// nice scalar
inline bool nice(float number);
// finite scalar
inline bool finite(float number);

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //
// min / max
template <typename T> inline const T min(const T &a, const T &b);
template <typename T> inline const T min(const T &a, const T &b, const T &c);
template <typename T> inline const T min(const T &a, const T &b, const T &c, const T &d);
template <typename T> inline const T max(const T &a, const T &b);
template <typename T> inline const T max(const T &a, const T &b, const T &c);
template <typename T> inline const T max(const T &a, const T &b, const T &c, const T &d);

// smallest / largest
template <typename T> inline const uint32_t smlst(const T &a, const T &b);
template <typename T> inline const uint32_t smlst(const T &a, const T &b, const T &c);
template <typename T> inline const uint32_t lrgst(const T &a, const T &b);
template <typename T> inline const uint32_t lrgst(const T &a, const T &b, const T &c);

// clamp
template <typename T> inline const T clamp(const T &t, const T &min, const T &max);

// range
template <typename T> inline bool range(const T &t, const T &min, const T &max);

} // namespace mth //
} // namespace gea //

#include "base.inl"

#endif // __GEA_BMTH_BASE_H__ //
