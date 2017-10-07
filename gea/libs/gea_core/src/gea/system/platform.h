#ifndef __GEA_PLATFORM_H__
#define __GEA_PLATFORM_H__

// gea includes
#include <gea/system/platform_intrinsic.h>

#if defined(GEA_WINXX)
    #include "platform_win32.h"
#elif defined(GEA_OSX)
    #include "platform_osx.h"
#else
    #error Unsupported platform!
#endif

// ------------------------------------------------------------------------- //
// Platform Interface                                                        //
/* ------------------------------------------------------------------------- //

// defines
typedef ? timestamp64_t;
typedef ? frequency_t;
typedef ? time32_t;
typedef ? time64_t;

// functions
inline timestamp64_t get_system_timestamp();
inline timestamp64_t get_system_frequency();
inline void system_sleep_seconds(const time32_t& t, bool interupt = false);

inline void break();

// ------------------------------------------------------------------------- */

#endif // __GEA_PLATFORM_H__ //
