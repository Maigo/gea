#pragma once

// ------------------------------------------------------------------------- //
// x86 intrinsic functions                                                   //
// ------------------------------------------------------------------------- //

namespace gea {

// ------------------------------------------------------------------------- //
// system functions                                                          //
// ------------------------------------------------------------------------- //
inline void i_system_break();

struct cpuid_info {
    uint32_t eax, ebx, ecx, edx;
};
inline void i_cpuid(cpuid_info& out_info, const uint32_t leaf, const uint32_t subleaf = 0);

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //
// trigonometry
inline void i_fsincos(float angle, float& out_sin, float& out_cos);
inline void i_fsin(float angle, float& out_sin);
inline void i_fcos(float angle, float& out_cos);

} // namespace gea //

#include "platform_intrinsic.inl"
