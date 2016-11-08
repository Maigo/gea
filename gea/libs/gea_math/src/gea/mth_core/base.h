#ifndef __GEA_MTH_CORE_BASE_H__
#define __GEA_MTH_CORE_BASE_H__

// std includes
#include <float.h>
#include <math.h>

// gea includes
#include <gea/mth_core/intrinsic.h>

// ------------------------------------------------------------------------- //
// global precompiler defines                                                //
// ------------------------------------------------------------------------- //
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

// ------------------------------------------------------------------------- //
// global static constants                                                   //
// ------------------------------------------------------------------------- //
// static constants
static const float PI          = 3.1415926535897932384626433832795f;
static const float SQRT_PI     = 1.7724538509055160272981674833411f;
static const float SQRT_PI_INV = 1.0f / SQRT_PI;
static const float SQRT_2      = 1.4142135623730950488016887242097f;
static const float SQRT_2_INV  = 1.0f / SQRT_2;
static const float E           = 2.7182818284590452353602874713527f;

// initialization markers
enum skip_initialization     { SKIP_INITIALIZATION };
enum identity_initialization { IDENTITY_INITIALIZATION };
enum zero_initialization     { ZERO_INITIALIZATION };

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //
// conversion functions
inline const float degrees_to_radians(const float deg);
inline const float radians_to_degrees(const float rad);
// optimized sin & cos method
inline void fsincos(const float angle, float &out_sin, float &out_cos);

// ------------------------------------------------------------------------- //
// arithmetic functions                                                      //
// ------------------------------------------------------------------------- //
// modulo
inline const float arithmetic_mod(const float value, const float mod);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
static const float APPROX_EPSILON = 1.0e-4f;
inline const bool approx_eq(const float f0, const float f1, const float e = APPROX_EPSILON);
inline const bool approx_ne(const float f0, const float f1, const float e = APPROX_EPSILON);

inline const bool approx_ls(const float f0, const float f1, const float e = APPROX_EPSILON);
inline const bool approx_gt(const float f0, const float f1, const float e = APPROX_EPSILON);

inline const bool approx_leq(const float f0, const float f1, const float e = APPROX_EPSILON);
inline const bool approx_geq(const float f0, const float f1, const float e = APPROX_EPSILON);

// approximative scalar
inline const float upb(const float f, const float e = APPROX_EPSILON); // upper bound
inline const float lwb(const float f, const float e = APPROX_EPSILON); // lower bound

// attributes
inline const bool nice(const float number);
inline const bool finite(const float number);

// round
template <typename T> inline const T round(const T v);
template <typename T> inline const T ceil(const T v);
template <typename T> inline const T floor(const T v);

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
template <typename T> inline const bool range(const T &t, const T &min, const T &max);

// sign
template <typename T> inline const int sign(const T x);

} // namespace mth //
} // namespace gea //

#include "base.inl"

#endif // __GEA_MTH_CORE_BASE_H__ //
