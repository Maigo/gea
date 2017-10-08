#pragma once

// gea includes
#include <gea/system/memory/allocator/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// proxy_allocator                                                           //
// ------------------------------------------------------------------------- //
class proxy_allocator : public allocator {
public:
    proxy_allocator(allocator *allocator, const char *name);
    virtual ~proxy_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(const void *p);

private:
    const char *m_name;
    allocator  *m_allocator;
};

// ------------------------------------------------------------------------- //

} // namespace gea //
