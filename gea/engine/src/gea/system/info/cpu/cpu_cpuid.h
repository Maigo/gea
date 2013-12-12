#ifndef __GEA_CPU_CPUID_H__
#define __GEA_CPU_CPUID_H__

#include <gea/engine/utility/bits.h>

namespace gea {
namespace cpu {

// ------------------------------------------------------------------------- //
// CPUID default leaf struct                                                 //
// ------------------------------------------------------------------------- //
struct cpuid_info {
    uint32_t eax, ebx, ecx, edx;
};

enum leaf_arg {
    STANDARD_0 = 0x00000000,
    STANDARD_1 = 0x00000001,
    STANDARD_2 = 0x00000002,
    STANDARD_3 = 0x00000003,
    STANDARD_4 = 0x00000004,
    STANDARD_5 = 0x00000005,
    STANDARD_6 = 0x00000006,
    STANDARD_7 = 0x00000007,
    STANDARD_8 = 0x00000008,
    STANDARD_9 = 0x00000009,
    STANDARD_A = 0x0000000A,
    STANDARD_B = 0x0000000B,
    STANDARD_C = 0x0000000C,
    STANDARD_D = 0x0000000D,
    EXTENDED_0 = 0x80000000,
    EXTENDED_1 = 0x80000001,
    EXTENDED_2 = 0x80000002,
    EXTENDED_3 = 0x80000003,
    EXTENDED_4 = 0x80000004,
    EXTENDED_5 = 0x80000005,
    EXTENDED_6 = 0x80000006,
    EXTENDED_7 = 0x80000007,
    EXTENDED_8 = 0x80000008
};

// ------------------------------------------------------------------------- //
// CPUID bit access functions                                                //
// ------------------------------------------------------------------------- //
//TODO: there must be a better way to do this? without branching and whatnot
template <typename T>
inline T bits(const T& ex, uint8_t from, uint8_t to) {
    register T mask = ~((~0u) << (to+1));
	if (to != 31) return ( mask & ex ) >> from;
    else          return ex >> from;
}

template <typename T>
inline T mask(const T& num, T* width) {
    T mask = bit::mask(num-1);
    if (width != NULL) *width = bit::ones(mask);
    return mask;
}

} // namespace cpu //
} // namespace gea //

#endif // __GEA_CPU_CPUID_H__ //
