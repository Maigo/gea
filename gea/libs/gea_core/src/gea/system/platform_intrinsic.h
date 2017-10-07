#ifndef __GEA_PLATFORM_INTRINSIC_H__
#define __GEA_PLATFORM_INTRINSIC_H__

// ------------------------------------------------------------------------- //
// x86 intrinsic functions                                                   //
// ------------------------------------------------------------------------- //

namespace gea {

// ------------------------------------------------------------------------- //
// System functions                                                          //
// ------------------------------------------------------------------------- //
inline void i_system_break();

} // namespace gea //

#if defined(GEA_MSVC)
#   include "platform_intrinsic_msvc.inl"
#elif defined(GEA_GCC)
#   include "platform_intrinsic_gcc.inl"
#else
#   error Unsupported compiler!
#endif

#endif // __GEA_PLATFORM_INTRINSIC_H__ //
