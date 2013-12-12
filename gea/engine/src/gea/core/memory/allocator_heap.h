#ifndef __GEA_ALLOCATOR_HEAP_H__
#define __GEA_ALLOCATOR_HEAP_H__

// gea includes
#include <gea/core/memory/allocator.h>

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
    virtual size_t allocated_size(void *p);

private:
    struct header {
        inline void init(const size_t &size);

        size_t  m_size;
    };

    const char *mp_name;
    size_t      m_alloc_size, m_alloc_cnt;
};

} // namespace gea //

#include "allocator_heap.inl"

#endif // __GEA_ALLOCATOR_HEAP_H__ //
