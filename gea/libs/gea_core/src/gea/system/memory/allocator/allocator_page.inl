#pragma once
#include "allocator_page.h"

namespace gea {

// ------------------------------------------------------------------------- //
// page_allocator                                                            //
// ------------------------------------------------------------------------- //
inline size_t page_allocator::size_to_pn(const size_t& size) const {
    return ((size + (m_page_size - 1)) / m_page_size);
}
inline size_t page_allocator::pn_to_size(const size_t& pn) const {
    return pn * m_page_size;
}

inline void page_allocator::header::init(const size_t &pages) {
    m_pages = pages;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
