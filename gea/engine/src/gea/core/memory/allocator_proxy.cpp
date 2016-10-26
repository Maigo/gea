// header include
#include "allocator_proxy.h"

namespace gea {

// ------------------------------------------------------------------------- //
// proxy_allocator                                                           //
// ------------------------------------------------------------------------- //
proxy_allocator::proxy_allocator(allocator *a, const char *name)
    : m_name(name), m_allocator(a) {}
proxy_allocator::~proxy_allocator() {}

void *proxy_allocator::allocate(size_t size, size_t align) {
    return m_allocator->allocate(size, align);
}
void proxy_allocator::deallocate(void *p) {
    m_allocator->deallocate(p);
}
size_t proxy_allocator::allocated_size(void *p) {
    return m_allocator->allocated_size(p);
}

} // namespace gea //
