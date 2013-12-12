#ifndef __GEA_PLATFORM_WIN32_H__
#define __GEA_PLATFORM_WIN32_H__

// std includes
//#define WIN32_LEAN_AND_MEAN
//#define WIN32_EXTRA_LEAN
#define NOMINMAX 
#include <windows.h>

#include "platform_intrinsic.h"

// ------------------------------------------------------------------------- //
// Platform global type definitions                                          //
// ------------------------------------------------------------------------- //
typedef LONGLONG timestamp64_t;
typedef LONGLONG frequency_t;
typedef float   time32_t;
typedef double  time64_t;

namespace gea {

//
//inline void *malloc_alligned(
//#define memalign(a,s) _aligned_malloc(s,a)

// ------------------------------------------------------------------------- //
// Platform time functions                                                   //
// ------------------------------------------------------------------------- //
// resolution scope
struct time_res_scope {
public:
    inline time_res_scope();
    inline ~time_res_scope();
private:
    TIMECAPS _tc;
};

inline timestamp64_t get_system_timestamp();
inline timestamp64_t get_system_frequency();
inline void system_sleep_seconds(const time32_t& t, bool interupt = false);

// ------------------------------------------------------------------------- //
// Platform system functions                                                 //
// ------------------------------------------------------------------------- //
inline void system_break();

} // namespace gea //

#include "platform_win32.inl"

#endif // __GEA_PLATFORM_WIN32_H__ //
