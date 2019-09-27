#pragma once

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //
// min / max
template <typename T> inline const T min(const T& a, const T& b);
template <typename T> inline const T min(const T& a, const T& b, const T& c);
template <typename T> inline const T min(const T& a, const T& b, const T& c, const T& d);
template <typename T> inline const T max(const T& a, const T& b);
template <typename T> inline const T max(const T& a, const T& b, const T& c);
template <typename T> inline const T max(const T& a, const T& b, const T& c, const T& d);

} // namespace mth //
} // namespace gea //

#include "math.inl"
