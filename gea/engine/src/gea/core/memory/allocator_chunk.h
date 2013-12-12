#ifndef __GEA_ALLOCATOR_CHUNK_H__
#define __GEA_ALLOCATOR_CHUNK_H__

// local gea includes
#include "allocator.h"

namespace gea {

// ------------------------------------------------------------------------- //
// chunk_allocator                                                           //
// ------------------------------------------------------------------------- //
class chunk_allocator : public allocator {
public:
    static const char *const DEFAULT_NAME;

    chunk_allocator(const char *name = DEFAULT_NAME);
    virtual ~chunk_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(void *p);

private:
    static const uint32_t DEFAULT_CHUNK_SIZE = 0x100000;

    struct chunk_header {
        uint32_t      m_size;
        chunk_header *m_prev;
        chunk_header *m_next;
    };

    const char *mp_name;
    size_t      m_alloc_size, m_alloc_cnt;
};

} // namespace gea //

#endif // __GEA_ALLOCATOR_CHUNK_H__ //
