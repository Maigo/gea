// header include
#include "allocator_heap.h"

// std includes
#include <stdio.h>

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// heap_allocator                                                            //
// ------------------------------------------------------------------------- //
const char *const heap_allocator::DEFAULT_NAME = "default_heap_allocator";
    
heap_allocator::heap_allocator(const char *name) : m_name(name), m_alloc_size(0), m_alloc_cnt(0) {}
heap_allocator::~heap_allocator() {
    l_assert_msg(m_alloc_size == 0 && m_alloc_cnt == 0, "Memory leak!");
}

void *heap_allocator::allocate(size_t size, size_t align) {
    // allocate set memory tag
    header *h = (header *) malloc(size + sizeof(header));
    l_fatal_assert_msg(h != nullptr, "Memory error!");
    h->init(size);

    // update stats
    m_alloc_size += (size + sizeof(header));
    m_alloc_cnt  += 1;
    return (void *) (h + 1);
}
void heap_allocator::deallocate(void *p) {
    // early out
    if (gea_unlikely(p == nullptr)) return;

    // deallocate
    header *h = ((header *) p) - 1;

    // update stats
    m_alloc_size -= (h->m_size + sizeof(header));
    m_alloc_cnt  -= 1;

    free(h);
}
size_t heap_allocator::allocated_size(const void *p) {
    header *h = ((header *) p) - 1;
    return h->m_size;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
