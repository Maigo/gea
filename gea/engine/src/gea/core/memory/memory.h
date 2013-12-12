#ifndef __GEA_MEMORY_H__
#define __GEA_MEMORY_H__

namespace gea {
namespace mem {

// ------------------------------------------------------------------------- //
// alignment                                                                 //
// ------------------------------------------------------------------------- //
template <typename T0, typename T1>
inline T0 roof(const T0& t, const T1& alignment);

template <typename T0, typename T1>
inline T0 floor(const T0& t, const T1& alignment);

} // namespace mem //
} // namespace gea //

#include "memory.inl"

#endif // __GEA_MEMORY_H__ //
