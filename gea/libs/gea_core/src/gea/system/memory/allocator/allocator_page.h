#pragma once

// gea includes
#include <gea/system/memory/allocator/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// page_allocator                                                            //
// ------------------------------------------------------------------------- //
class page_allocator : public allocator {
public:
    static const char *const DEFAULT_NAME;

    explicit page_allocator(const char *name = DEFAULT_NAME);
    virtual ~page_allocator();

    virtual void *allocate(size_t size, size_t align);
    virtual void deallocate(void *p);
    virtual size_t allocated_size(const void *p);

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

    const char *m_name;
    size_t      m_page_size;
    size_t      m_alloc_size, m_alloc_cnt;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "allocator_page.inl"
