#ifndef __GEA_ALLOCATOR_LINKED_H__
#define __GEA_ALLOCATOR_LINKED_H__

// local gea includes
#include "allocator.h"

namespace gea {

class linked_allocator : public allocator {
public:
    linked_allocator(allocator *allocator);
    virtual ~linked_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(void *p);

private:
    struct header {
        inline header();
        inline void link_after(header *h);
        inline void link_before(header *h);
        inline void insert_after(header *h);
        inline void insert_before(header *h);
        inline void remove() const;

        header *prev, *next;
    };

    // link structure anchor
    header m_head, m_tail;

    // backend allocator
    allocator *m_allocator;
};

} // namespace gea //

#include "allocator_linked.inl"

#endif // __GEA_ALLOCATOR_LINKED_H__ //
