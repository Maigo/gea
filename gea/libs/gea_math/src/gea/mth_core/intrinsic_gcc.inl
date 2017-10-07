#pragma once
#include "intrinsic.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //
// trigonometry
inline void i_fsincos(float angle, float &out_sin, float &out_cos) {
    __asm {
        fld dword ptr [angle]
        fsincos
        mov ebx, [out_cos]      ; get the pointer into ebx
        fstp dword ptr [ebx]    ; store the result through the pointer
        mov ebx, [out_sin]
        fstp dword ptr [ebx]
    }
}
    
// attributes
inline const bool i_fisnan(const float number) {
    return isnan(number);
}
inline const bool i_ffinite(const float number) {
    return isfinite(number);
}
} // namespace mth //
} // namespace gea //
