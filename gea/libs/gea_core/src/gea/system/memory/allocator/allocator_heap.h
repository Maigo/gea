#pragma once

// gea includes
#include <gea/system/memory/allocator/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// heap allocator                                                            //
// ------------------------------------------------------------------------- //
class heap_allocator : public allocator {
public:
    static const char *const DEFAULT_NAME;

    heap_allocator(const char *name = DEFAULT_NAME);
    virtual ~heap_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(const void *p);

private:
    struct header {
        inline void init(const size_t &size);

        size_t  m_size;
    };

    const char *m_name;
    size_t      m_alloc_size, m_alloc_cnt;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "allocator_heap.inl"
