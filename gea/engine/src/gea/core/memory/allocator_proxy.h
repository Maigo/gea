#ifndef __GEA_ALLOCATOR_PROXY_H__
#define __GEA_ALLOCATOR_PROXY_H__

// gea includes
#include <gea/core/memory/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// proxy_allocator                                                           //
// ------------------------------------------------------------------------- //
class proxy_allocator : public allocator {
public:
    proxy_allocator(allocator *a, const char *name);
    virtual ~proxy_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(void *p);

private:
    const char *m_name;
    allocator  *m_allocator;
};

} // namespace gea //

#endif // __GEA_ALLOCATOR_PROXY_H__ //
