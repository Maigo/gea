#ifndef __GEA_GLOBAL_H__
#define __GEA_GLOBAL_H__

// make sure this file is only included when compiling strictly c++ files
#if defined(__cplusplus)

// ------------------------------------------------------------------------- //
// Global typedef's                                                          //
// ------------------------------------------------------------------------- //
#include <stdint.h>

typedef uint8_t byte;

// ------------------------------------------------------------------------- //
// Compiler specific globals                                                 //
// ------------------------------------------------------------------------- //
#include "compiler.h"

#endif // c++ //

#endif // __GEA_GLOBAL_H__ //