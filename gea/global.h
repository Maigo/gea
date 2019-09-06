#ifndef __GEA_GLOBAL_H__
#define __GEA_GLOBAL_H__

// make sure this file is only included when compiling strictly c++ files
#if defined(__cplusplus)

// ------------------------------------------------------------------------- //
// Global typedef's                                                          //
// ------------------------------------------------------------------------- //
#include <stdint.h>

typedef uint8_t byte;

typedef char char8_t;
typedef unsigned char uchar8_t;

// ------------------------------------------------------------------------- //
// Compiler specific globals                                                 //
// ------------------------------------------------------------------------- //
#include "compiler.h"

#endif // c++ //

#endif // __GEA_GLOBAL_H__ //