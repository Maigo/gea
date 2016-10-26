// header include
#include "allocator_page.h"

// gea includes
#include <gea/system/memory_virtual.h>
#include <gea/utility/assert.h>

namespace gea {

const char *const page_allocator::DEFAULT_NAME = "default_page_allocator";

page_allocator::page_allocator(const char *name) : mp_name(name), m_page_size(0),  m_alloc_size(0), m_alloc_cnt(0) {
    // determine page file size
    m_page_size = mem::get_page_size();
}

page_allocator::~page_allocator() {
    l_assert_msg(m_alloc_size == 0 && m_alloc_cnt == 0, "Memory leak!");
}

void *page_allocator::allocate(size_t size, size_t align) {
    // calculate number of pages needed
    size_t pages = size_to_pn(size + sizeof(header));

    // allocate set memory tag
    header *h = (header *) mem::virtual_allocate(pn_to_size(pages));
    l_assert_msg(h != NULL, "Memory error!");
    h->init(pages);

    // update stats
    m_alloc_size += pn_to_size(pages);
    m_alloc_cnt  += 1;
    return (void *) (h + 1);
}
void page_allocator::deallocate(void *p) {
    // early out
	if (gea_unlikely(p == NULL)) return;

    // deallocate
    header *h = ((header *) p) - 1;

    // update stats
    m_alloc_size -= pn_to_size(h->m_pages);
    m_alloc_cnt  -= 1;

    mem::virtual_deallocate(h);
}
size_t page_allocator::allocated_size(void *p) {
    header *h = ((header *) p) - 1;
    return pn_to_size(h->m_pages) - sizeof(header);
}

//void vm_allocator::reserve(const size_t &size) {}

} // namespace gea //
