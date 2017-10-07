#ifndef __GEA_MEMORY_VIRTUAL_H__
#define __GEA_MEMORY_VIRTUAL_H__

#if defined(GEA_WINXX)
#   include "memory_virtual_win32.h"
#elif defined(GEA_OSX)
#   include "memory_virtual_osx.h"
#else
#   error Unsupported platform!
#endif

// ------------------------------------------------------------------------- //
// Virtual Memory Interface                                                  //
/* ------------------------------------------------------------------------- //

// defines

// functions

// ------------------------------------------------------------------------- */

#endif // __GEA_MEMORY_VIRTUAL_H__ //
