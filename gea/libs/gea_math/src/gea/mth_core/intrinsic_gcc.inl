#pragma once
#include "intrinsic.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //
// trigonometry
inline void i_fsincos(float angle, float &out_sin, float &out_cos) {
    __asm ("fsincos" : "=t" (out_cos), "=u" (out_sin) : "0" (angle));
}

// attributes
inline const bool i_fisnan(const float number) {
    return isnan(number);
}
inline const bool i_ffinite(const float number) {
    return isfinite(number);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
