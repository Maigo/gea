#ifndef __GEA_MEMORY_VIRTUAL_WIN32_H__
#define __GEA_MEMORY_VIRTUAL_WIN32_H__

// gea engine includes
#include <gea/system/platform.h>

namespace gea {
namespace mem {

size_t get_page_size() { 
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return static_cast<size_t>(si.dwPageSize);
}

void *virtual_allocate(const size_t &size) {
    return VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
}

void virtual_deallocate(void *p) {
    VirtualFree(p, 0, MEM_RELEASE);
}

} // namespace mem //
} // namespace gea //

#endif // __GEA_MEMORY_VIRTUAL_WIN32_H__ //
