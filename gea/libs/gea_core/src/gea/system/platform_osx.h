#ifndef __GEA_PLATFORM_OSX_H__
#define __GEA_PLATFORM_OSX_H__

// ------------------------------------------------------------------------- //
// Platform global type definitions                                          //
// ------------------------------------------------------------------------- //
typedef int64_t timestamp64_t;
typedef int64_t frequency_t;
typedef float   time32_t;
typedef double  time64_t;

namespace gea {

//
//inline void *malloc_alligned(
//#define memalign(a,s) _aligned_malloc(s,a)

// ------------------------------------------------------------------------- //
// Platform time functions                                                   //
// ------------------------------------------------------------------------- //
inline timestamp64_t get_system_timestamp() { return 0; }
inline timestamp64_t get_system_frequency() { return 0; }
inline void system_sleep_seconds(const time32_t& t, bool interupt = false) {}

// ------------------------------------------------------------------------- //
// Platform system functions                                                 //
// ------------------------------------------------------------------------- //
inline void system_break();

} // namespace gea //

#include "platform_osx.inl"

#endif // __GEA_PLATFORM_OSX_H__ //
