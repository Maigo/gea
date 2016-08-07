
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //
// trigonometry
inline void i_fsincos(float angle, float &sin, float &cos) {
    _asm {
        fld dword ptr [angle]
        fsincos
        mov ebx, [cos]          ; get the pointer into ebx
        fstp dword ptr [ebx]    ; store the result through the pointer
        mov ebx, [sin]
        fstp dword ptr [ebx]
    }
}

} // namespace mth //
} // namespace gea //
