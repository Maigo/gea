#ifndef __GEA_INTRINSICS_GCC_H__
#define __GEA_INTRINSICS_GCC_H__

// ------------------------------------------------------------------------- //
// Compiler Specific Inline Assembly Functions                               //
// ------------------------------------------------------------------------- //

// system information
inline bool ci_has_cpuid() {
    // TODO: implement!
    return false;
}
inline void ci_cpuid(void* info, const uint32_t leaf, const uint32_t subleaf = 0) {
}

#endif // __GEA_INTRINSICS_GCC_H__ //
