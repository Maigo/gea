// header include
#include "allocator_linked.h"

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// allocator_linked                                                          //
// ------------------------------------------------------------------------- //
linked_allocator::linked_allocator(allocator *allocator)
    : m_head(), m_tail(), m_allocator(allocator)
{
    // link stubs
    m_tail.link_after(&m_head);
}
linked_allocator::~linked_allocator() {}

void *linked_allocator::allocate(size_t size, size_t align) {
    // allocate memory
    header *p = (header *) m_allocator->allocate(size, align);
    // link to head
    p->insert_after(&m_head);

    return (void *) (p + 1);
}
void linked_allocator::deallocate(void *p) {
    // early out
    l_assert(p != nullptr);
	if (gea_unlikely(p == nullptr)) return;

    // unlink
    header *h = (header *) p - 1;
    h->remove();
    // deallocate memory
    m_allocator->deallocate(h);
}
size_t linked_allocator::allocated_size(const void *p) {
    return m_allocator->allocated_size((const header *) p - 1) - sizeof(header);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
