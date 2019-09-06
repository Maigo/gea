#pragma once

// header include
#include "platform_intrinsic.h"

extern "C" void asm_system_break();
extern "C" void asm_cpuid(void* info, const uint32_t leaf, const uint32_t subleaf);
extern "C" void asm_fsincos(float angle, float* out_sin, float* out_cos);
extern "C" void asm_fsin(float angle, float* out_sin);
extern "C" void asm_fcos(float angle, float* out_cos);

namespace gea {

// ------------------------------------------------------------------------- //
// system functions                                                          //
// ------------------------------------------------------------------------- //

inline void i_system_break() {
    asm_system_break();
}

inline void i_cpuid(cpuid_info& out_info, const uint32_t leaf, const uint32_t subleaf) {
    asm_cpuid(&out_info, leaf, subleaf);
}

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //

// trigonometry
inline void i_fsincos(float angle, float& out_sin, float& out_cos) {
    asm_fsincos(angle, &out_sin, &out_cos);
}
inline void i_fsin(float angle, float& out_sin) {
    asm_fsin(angle, &out_sin);
}
inline void i_fcos(float angle, float& out_cos) {
    asm_fcos(angle, &out_cos);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
