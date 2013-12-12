#ifndef __GEA_MATH_H__
#define __GEA_MATH_H__

namespace gea {
namespace math {

// ------------------------------------------------------------------------- //
// Utility Functions                                                         //
// ------------------------------------------------------------------------- //
template <class V, class S>
inline V lerp(const V& v1, const V& v2, S s);

template <typename T>
inline const T& clamp(const T& x, const T& low, const T& high);

// ------------------------------------------------------------------------- //
// Template functions                                                        //
// ------------------------------------------------------------------------- //
template <class InputIterator, class T>
inline T mean(InputIterator first, InputIterator last, T init);

} // namespace math //
} // namespace gea //

#include "math.inl"

#endif // __GEA_MATH_H__ //
