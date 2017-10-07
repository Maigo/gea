#ifndef __GEA_INTRINSICS_H__
#define __GEA_INTRINSICS_H__

#if   defined _MSC_VER
    #include "intrinsics_msvc.h"
#elif defined __GNUC__
    #include "intrinsics_gcc.h"
#else
    #error Unsupported compiler!
#endif

#endif // __GEA_INTRINSICS_H__ //
