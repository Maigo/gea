#ifndef __GEA_COMPILER_H__
#define __GEA_COMPILER_H__

#if   defined _MSC_VER
    #include "compiler_msvc.h"
#elif defined __GNUC__
    #include "compiler_gcc.h"
#else
    #error Unsupported compiler!
#endif

// ------------------------------------------------------------------------- //
// compiler switch                                                           //
// ------------------------------------------------------------------------- //
#ifndef MSVC_VER
    #define MSVC_VER(maj,min) FALSE
#endif
#ifndef GCC_VER
    #define GCC_VER(maj,min)  FALSE
#endif

// ------------------------------------------------------------------------- //
// compiler independent functionality                                        //
// ------------------------------------------------------------------------- //

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(type_name)         \
    type_name(const type_name&);                    \
    void operator=(const type_name&)    
// A macro to disallow the default constructor
// This should be used in the private: declarations for a class
#define DISALLOW_DEFAULT_CTOR(type_name)            \
    type_name();

#endif // __GEA_COMPILER_H__ //
