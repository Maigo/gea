#ifndef __GEA_COMPILER_GCC_H__
#define __GEA_COMPILER_GCC_H__

// ------------------------------------------------------------------------- //
// Define private compiler specific helper functions                          //
// ------------------------------------------------------------------------- //
#define GCC_VER(maj, min) \
    ( (__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min) )
// ------------------------------------------------------------------------- //

#define gea_force_inline    __forceinline

#define gea_sizeof(x)       sizeof(x)
#define gea_sizeof_array(x) (sizeof(x) / sizeof((x)[0])
#define gea_alignof(x)      __alignof(x)

#define gea_alignment(x)    //TODO: alignment?
#error alignment is not implemented yet!

#define gea_likely(c)   __builtin_expect(c,1)
#define gea_unlikely(c) __builtin_expect(c,0)

//#define __LINE__ __LINE__
//#define __FILE__ __FILE__
#define __FUNC__ __PRETTY_FUNCTION__

// ------------------------------------------------------------------------- //
// Compiler Intrinsics                                                        //
// ------------------------------------------------------------------------- //
// byte swap
#if GCC_VER(4,3)
    #define INTRINSIC_BYTE_SWAP
    inline void byte_swap16(uint16_t &x) { x = __builtin_bswap16(x); }
    inline void byte_swap32(uint32_t &x) { x = __builtin_bswap32(x); }
    inline void byte_swap64(uint64_t &x) { x = __builtin_bswap64(x); }
#else
    #error Intrinsic byte swap not supported!
    inline void byte_swap16(uint16_t &x) { } 
    inline void byte_swap32(uint32_t &x) { }
    inline void byte_swap64(uint64_t &x) { }
#endif // gcc 4.3 or above //

// ------------------------------------------------------------------------- //
// Undefine private compiler specific helper functions                        //
// ------------------------------------------------------------------------- //
//#undef GCC_VER
// ------------------------------------------------------------------------- //

#endif // __GEA_COMPILER_GCC_H__ //
