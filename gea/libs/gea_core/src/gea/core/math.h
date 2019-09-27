#pragma once

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //
// min / max
template <typename T> inline const T min(const T& t0, const T& t1);
template <typename T, typename... Ts> inline const T min(const T& t0, const T& t1, const Ts& ... ts);
template <typename T> inline const T max(const T& t0, const T& t1);
template <typename T, typename... Ts> inline const T max(const T& t0, const T& t1, const Ts& ... ts);

} // namespace mth //
} // namespace gea //

#include "math.inl"
