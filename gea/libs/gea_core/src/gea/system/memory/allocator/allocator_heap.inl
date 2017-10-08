#pragma once
#include "allocator_heap.h"

namespace gea {

// ------------------------------------------------------------------------- //
// allocator_heap                                                            //
// ------------------------------------------------------------------------- //
inline void heap_allocator::header::init(const size_t &size) {
    m_size = size;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
