#pragma once

// header include
#include "math.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //
// max / min
template <typename T> inline const T min(const T& a, const T& b) { return (a > b ? b : a); }
template <typename T> inline const T min(const T& a, const T& b, const T& c) { return min(a, min(b, c)); }
template <typename T> inline const T min(const T& a, const T& b, const T& c, const T& d) { return min(a, min(b, min(c, d))); }
template <typename T> inline const T max(const T& a, const T& b) { return (a < b ? b : a); }
template <typename T> inline const T max(const T& a, const T& b, const T& c) { return max(a, max(b, c)); }
template <typename T> inline const T max(const T& a, const T& b, const T& c, const T& d) { return max(a, max(b, max(c, d))); }

} // namespace mth //
} // namespace gea //
