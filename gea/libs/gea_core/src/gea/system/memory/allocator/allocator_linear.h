#pragma once

// gea includes
#include <gea/system/memory/allocator/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// linear_allocator                                                          //
// ------------------------------------------------------------------------- //
class linear_allocator : public allocator {
public:
    linear_allocator(allocator *allocator, size_t size);
    virtual ~linear_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(const void *p);

private:
    inline void *align_ptr(const void *p, const size_t &align) const;

    struct header {
        uint32_t m_size;
    };

    // allocator stats
    size_t   m_alloc_size;
    uint32_t m_alloc_cnt;

    // linear ptr
    uint8_t *m_head, *m_tail;

    // back end allocator
    allocator *m_allocator;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "allocator_linear.inl"
