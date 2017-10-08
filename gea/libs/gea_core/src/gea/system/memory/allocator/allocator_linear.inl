#pragma once
#include "allocator_linear.h"

namespace gea {

// ------------------------------------------------------------------------- //
// linear_allocator                                                          //
// ------------------------------------------------------------------------- //
inline void *linear_allocator::align_ptr(const void *p, const size_t &align) const {
    return (void *) (((uintptr_t) p + (align - 1)) & ~(align - 1));
}

// ------------------------------------------------------------------------- //

} // namespace gea //
