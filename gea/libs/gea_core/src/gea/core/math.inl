#pragma once

// header include
#include "math.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //
// max / min
template <typename T> inline const T min(const T& t0, const T& t1) {
    return (t0 > t1 ? t1 : t0);
}
template <typename T, typename... Ts> inline const T min(const T& t0, const T& t1, const Ts& ... ts) {
    return min(t0, min(t1, ts...));
}
template <typename T> inline const T max(const T& t0, const T& t1) {
    return (t0 < t1 ? t1 : t0);
}
template <typename T, typename... Ts> inline const T max(const T& t0, const T& t1, const Ts& ... ts) {
    return max(t0, max(t1, ts...));
}

} // namespace mth //
} // namespace gea //
