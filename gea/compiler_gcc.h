#ifndef __GEA_COMPILER_GCC_H__
#define __GEA_COMPILER_GCC_H__

// global includes
#include <stdlib.h>

#include "intrinsics.h"

// ------------------------------------------------------------------------- //
// Compiler specific Precompiler Definitions                                 //
// ------------------------------------------------------------------------- //
#define GEA_GCC

#if defined(_WIN64)
#   define GEA_WINXX
#   define GEA_WIN64
#elif defined(_WIN32)
#   define GEA_WINXX
#   define GEA_WIN32
#elif defined(__APPLE__) && defined(__MACH__)
#   include "TargetConditionals.h"
#   // iOS Simulator
#   if TARGET_IPHONE_SIMULATOR == 1
#       error "Unsupported Apple platform: iOS Simulator!"
#   // iOS Device
#   elif TARGET_OS_IPHONE == 1
#       error "Unsupported Apple platform: iOS Device!"
#   // Other Mac OS
#   elif TARGET_OS_MAC == 1
#       define GEA_OSX
#   else
#       error "Unsupported Apple platform!"
#   endif
#else
#   error "Unsupported platform!"
#endif

// ------------------------------------------------------------------------- //
// Define private compiler specific helper functions                         //
// ------------------------------------------------------------------------- //
#define GCC_VER(major, minor, patch) \
    ((__GNUC__ << 16) + (__GNUC_MINOR__ << 8) + (__GNUC_PATCHLEVEL__) >= \
     ((major) << 16) + ((minor) << 8) + (patch))
// ------------------------------------------------------------------------- //

#define gea_inline          inline
#define gea_force_inline    __attribute__((always_inline))

#define gea_sizeof(x)       sizeof(x)
#define gea_alignof(x)      __alignof(x)
#define gea_alignment(x)    __attribute__((aligned (x)))

#define gea_likely(c)   __builtin_expect(c,1)
#define gea_unlikely(c) __builtin_expect(c,0)

#if GCC_VER(4,7,0)
#   define gea_unused __attribute__((unused))
#else
#   define gea_unused
#endif // gcc 4.7 or above

//#define __LINE__ __LINE__
//#define __FILE__ __FILE__
#define __FUNC__ __PRETTY_FUNCTION__

// ------------------------------------------------------------------------- //
// Compiler Intrinsics                                                       //
// ------------------------------------------------------------------------- //
// byte swap
#if GCC_VER(4,3,0)
#   define INTRINSIC_BYTE_SWAP
inline void byte_swap16(uint16_t &x) { x = __builtin_bswap16(x); }
inline void byte_swap32(uint32_t &x) { x = __builtin_bswap32(x); }
inline void byte_swap64(uint64_t &x) { x = __builtin_bswap64(x); }
#else
inline void byte_swap16(uint16_t &x) { x = (((x & 0xFF00) >> 8) |
                                            ((x & 0x00FF) << 8));}
inline void byte_swap32(uint32_t &x) { x = (((x & 0xFF000000) >> 24) |
                                            ((x & 0x00FF0000) >>  8) |
                                            ((x & 0x0000FF00) <<  8) |
                                            ((x & 0x000000FF) << 24)); }
inline void byte_swap64(uint64_t &x) { x = (((x & 0xFF00000000000000) >> 56) |
                                            ((x & 0x00FF000000000000) >> 40) |
                                            ((x & 0x0000FF0000000000) >> 24) |
                                            ((x & 0x000000FF00000000) >>  8) |
                                            ((x & 0x00000000FF000000) <<  8) |
                                            ((x & 0x0000000000FF0000) << 24) |
                                            ((x & 0x000000000000FF00) << 40) |
                                            ((x & 0x00000000000000FF) << 56)); }
#endif // gcc 4.3 or above //

// ------------------------------------------------------------------------- //
// Undefine private compiler specific helper functions                        //
// ------------------------------------------------------------------------- //
//#undef GCC_VER
// ------------------------------------------------------------------------- //

#endif // __GEA_COMPILER_GCC_H__ //
