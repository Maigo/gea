#ifndef __GEA_MEMORY_H__
#define __GEA_MEMORY_H__

// gea engine includes
#include <gea/system/platform.h>

namespace gea {
namespace mem {

inline void zero_memory(void* ptr, size_t size) { ZeroMemory( ptr, size ); }

} // namespace mem //
} // namespace gea //

#endif // __GEA_MEMORY_H__ //
