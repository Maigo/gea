#pragma once

// gea includes
#include <gea/system/memory/allocator/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// pool_allocator                                                            //
// ------------------------------------------------------------------------- //
class pool_allocator : public allocator {
public:
    static const char *const DEFAULT_NAME;

    pool_allocator(const char *name = DEFAULT_NAME);
    virtual ~pool_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void dealocate(void *p);
    virtual size_t allocated_size(const void *p);

private:

    const char *m_name;
    size_t      m_alloc_size, m_alloc_cnt;
};

// ------------------------------------------------------------------------- //

} // namespace gea //
