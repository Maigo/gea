// header include
#include "allocator_proxy.h"

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// proxy_allocator                                                           //
// ------------------------------------------------------------------------- //
proxy_allocator::proxy_allocator(allocator *allocator, const char *name)
    : m_name(name), m_allocator(allocator) { l_fatal_assert(m_allocator); }
proxy_allocator::~proxy_allocator() {}

void *proxy_allocator::allocate(size_t size, size_t align) {
    l_fatal_assert(m_allocator);
    return m_allocator->allocate(size, align);
}
void proxy_allocator::deallocate(void *p) {
    l_fatal_assert(m_allocator);
    m_allocator->deallocate(p);
}
size_t proxy_allocator::allocated_size(const void *p) {
    l_fatal_assert(m_allocator);
    return m_allocator->allocated_size(p);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
