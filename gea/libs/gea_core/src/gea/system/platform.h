#ifndef __GEA_PLATFORM_H__
#define __GEA_PLATFORM_H__

#if defined(WIN32)
    #include "platform_win32.h"
#else
    #error Unsupported platform!
#endif

// ------------------------------------------------------------------------- //
// platform global type definitions                                          //
/* ------------------------------------------------------------------------- //
typedef ? timestamp64_t;
typedef ? frequency_t;
typedef ? time32_t;
typedef ? time64_t;

// ------------------------------------------------------------------------- //
// platform variables                                                        //
// ------------------------------------------------------------------------- //
static const char path_separator = ?;

// ------------------------------------------------------------------------- //
// platform time functions                                                   //
// ------------------------------------------------------------------------- //
inline timestamp64_t get_system_timestamp();
inline timestamp64_t get_system_frequency();
inline void system_sleep_seconds(const time32_t& t, bool interupt = false);

// ------------------------------------------------------------------------- //
// platform system functions                                                 //
// ------------------------------------------------------------------------- //
inline void system_break();

// ------------------------------------------------------------------------- */

#endif // __GEA_PLATFORM_H__ //
