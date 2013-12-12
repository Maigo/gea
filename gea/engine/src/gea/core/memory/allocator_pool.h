#ifndef __GEA_ALLOCATOR_POOL_H__
#define __GEA_ALLOCATOR_POOL_H__

// local gea includes
#include "allocator.h"

namespace gea {

// ------------------------------------------------------------------------- //
// pool_allocator                                                            //
// ------------------------------------------------------------------------- //
class pool_allocator : public allocator {
public:
    static const char *const DEFAULT_NAME;

    pool_allocator(const char *name = DEFAULT_NAME);
    virtual ~pool_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void dealocate(void *p);
    virtual size_t allocated_size(void *p);

private:

    const char *mp_name;
    size_t      m_alloc_size, m_alloc_cnt;
};

} // namespace gea //

#endif // __GEA_ALLOCATOR_POOL_H__ //
