#pragma once

// header include
#include "memory_util.h"

// gea includes
#include <gea/core/bits/bits.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// memory util                                                               //
// ------------------------------------------------------------------------- //

template <typename T>
static inline T* memory_util::align(T* const p, const size_t align) {
    l_assert_msg(bit::is_pow2(align), "Must align to power of 2!");
    return reinterpret_cast<T*>((reinterpret_cast<uintptr_t>(p) + (align - 1)) & ~(align - 1));
}

// ------------------------------------------------------------------------- //

} // namespace gea //
