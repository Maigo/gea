#ifndef __GEA_ALLOCATOR_LINEAR_H__
#define __GEA_ALLOCATOR_LINEAR_H__

// local gea includes
#include "allocator.h"

namespace gea {

// ------------------------------------------------------------------------- //
// linear_allocator                                                          //
// ------------------------------------------------------------------------- //
class linear_allocator : public allocator {
public:
    linear_allocator(allocator *a, size_t size);
    virtual ~linear_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(void *p);

private:
    inline void *align_ptr(const void *p, const size_t &align) const;

    struct header {
        uint32_t m_size;
    };

    // linear ptr
    uint8_t *m_head, *m_tail;

    // allocator stats
    size_t   m_alloc_size;
    uint32_t m_alloc_cnt;

    // back end allocator
    allocator *m_allocator;
};

} // namespace gea //

#include "allocator_linear.inl"

#endif // __GEA_ALLOCATOR_LINEAR_H__ //
