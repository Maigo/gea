#ifndef __GEA_MEMORY_VIRTUAL_OSX_H__
#define __GEA_MEMORY_VIRTUAL_OSX_H__

// osx includes
#include <unistd.h>

// gea engine includes
#include <gea/system/platform.h>

namespace gea {
namespace mem {

size_t get_page_size() { 
    const int page_size = getpagesize();
    return static_cast<size_t>(page_size);
}

void *virtual_allocate(const size_t &size) {
    return nullptr;
}

void virtual_deallocate(void *p) {
}

} // namespace mem //
} // namespace gea //

#endif // __GEA_MEMORY_VIRTUAL_OSX_H__ //
