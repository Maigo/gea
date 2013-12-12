#ifndef __H_ALLOCATOR_VIRTUAL_H__
#define __H_ALLOCATOR_VIRTUAL_H__

// local gea include
#include "allocator.h"

namespace gea {

class page_allocator : public allocator {
public:
    static const char *const DEFAULT_NAME;

    explicit page_allocator(const char *name = DEFAULT_NAME);
    virtual ~page_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(void *p);

    // virtual memory specific functions
//    void reserve(const size_t &size);

private:
    inline size_t size_to_pn(const size_t &size) const;
    inline size_t pn_to_size(const size_t &pn) const;

    // each separate allocated page(s) is tagged with this header
    struct header {
        inline void init(const size_t &pages);
        size_t m_pages;
    };

    const char *mp_name;
    size_t      m_page_size;
    size_t      m_alloc_size, m_alloc_cnt;
};

} // namespace gea //

#include "allocator_page.inl"

#endif // __H_ALLOCATOR_VIRTUAL_H__ //
