#ifndef __GEA_COMPILER_MSVC_H__
#define __GEA_COMPILER_MSVC_H__

#include <intrin.h>
#include "intrinsics.h"

// ------------------------------------------------------------------------- //
// Define private compiler specific helper functions                         //
// ------------------------------------------------------------------------- //
#define MSVC_MAJOR ( (_MSC_VER % 10000 ) / 100 )
#define MSVC_MINOR ( (_MSC_VER %   100 ) /   1 )
#define MSVC_VER(maj, min) \
    ( (MSVC_MAJOR << 16) + MSVC_MINOR >= ((maj) << 16) + (min) )
// ------------------------------------------------------------------------- //

#define gea_force_inline    __forceinline

#define gea_alignof(x)      __alignof(x)

#define gea_alignment(x)    __declspec(align(x))

#define gea_likely(c)       (c)
#define gea_unlikely(c)     (c)

//#define __LINE__ __LINE__
//#define __FILE__ __FILE__
#define __FUNC__ __FUNCSIG__

// ------------------------------------------------------------------------- //
// Compiler Intrinsics                                                       //
// ------------------------------------------------------------------------- //

// byte swap
#define INTRINSIC_BYTE_SWAP
inline void byte_swap16(uint16_t &x) { x = _byteswap_ushort(x); }
inline void byte_swap32(uint32_t &x) { x = _byteswap_ulong(x); }
inline void byte_swap64(uint64_t &x) { x = _byteswap_uint64(x); }

// system information
#define gea_has_cpuid()     ci_has_cpuid()
#define gea_cpuid(x,y)      ci_cpuid(x,y)
//#define cpuid(x,y)      __cpuid(x,y)

// ------------------------------------------------------------------------- //
// Undefine private compiler specific helper functions                       //
// ------------------------------------------------------------------------- //
#undef MSVC_MAJOR
#undef MSVC_MINOR
//#undef MSVC_VER
// ------------------------------------------------------------------------- //

#endif // __GEA_COMPILER_MSVC_H__ //
