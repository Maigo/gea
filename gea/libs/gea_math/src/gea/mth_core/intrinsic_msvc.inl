#pragma once
#include "intrinsic.h"

// std includes
#include <float.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //
// trigonometry
inline void i_fsincos(float angle, float &out_sin, float &out_cos) {
    _asm {
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
    return _isnan(number) != 0;
}
inline const bool i_ffinite(const float number) {
    return _finite(number) != 0;
}

} // namespace mth //
} // namespace gea //
