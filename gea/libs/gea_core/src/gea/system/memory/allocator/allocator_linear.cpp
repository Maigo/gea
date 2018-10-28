// header include
#include "allocator_linear.h"

// gea includes
#include <gea/system/memory/memory_util.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// linear_allocator                                                          //
// ------------------------------------------------------------------------- //
linear_allocator::linear_allocator(allocator *allocator, size_t size)
    : m_head(nullptr), m_tail(nullptr), m_alloc_size(0), m_alloc_cnt(0), m_allocator(allocator)
{
    m_head = (uint8_t *) m_allocator->allocate(size, 1);
    m_tail = m_head + size;
}
linear_allocator::~linear_allocator() {
    l_assert_msg(m_alloc_size == 0 && m_alloc_cnt == 0, "Memory leak!");
    m_allocator->deallocate(m_head);
}

void *linear_allocator::allocate(size_t size, size_t align) {
    uint8_t *p = m_head;

    // allocate memory tag
    p += sizeof(header);
    // align
    p  = memory_util::align(p, align);

    l_assert_msg((p + size) < m_tail, "Out of memory!");

    // tag memory
    header *h = ((header *) p) - 1;
    h->m_size = size;

    // update stats
    m_alloc_size += ((p + size) - m_head);
    m_alloc_cnt  += 1;

    // bump pointer
    m_head = p + size;

    return p;
}
void linear_allocator::deallocate(void *p) {
    header *h = (((header *) p) - 1);
    // this assert may detect invalid deallocations
    l_assert_msg(0 < h->m_size && h->m_size <= m_alloc_size, "Invalid memory tag detected!");

    m_alloc_size -= h->m_size;
    m_alloc_cnt  -= 1;
}
size_t linear_allocator::allocated_size(const void *p) {
    const header *h = (((const header *) p) - 1);
    // this assert may detect invalid deallocations
    l_assert_msg(0 < h->m_size && h->m_size <= m_alloc_size, "Invalid memory tag detected!");

    return h->m_size;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
