#pragma once
#include "allocator.h"

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// allocator                                                                 //
// ------------------------------------------------------------------------- //
template <class T, typename ... Args>
inline T *allocator::make_new(Args ... args) {
    void* const p = allocate(gea_sizeof(T), gea_alignof(T));
    return gea_likely(p != nullptr) ? new (p) T(args...) : nullptr;
}

template <class T>
inline void allocator::make_delete(T *p) {
    if (gea_likely(p != nullptr)) {
        p->~T();
        deallocate(p);
    }
}

// ------------------------------------------------------------------------- //
//                                                                           //
// ------------------------------------------------------------------------- //
inline void *allocate_memory(allocator *allocator, const size_t &size, const size_t &align) {
    l_fatal_assert(allocator != nullptr);
    return allocator->allocate(size, align);
}
inline void deallocate_memory(allocator *allocator, void *p, const size_t &size) {
    l_fatal_assert(allocator != nullptr);
    allocator->deallocate(p);
}

template <class T>
inline void *allocate_object(allocator *allocator, const size_t &n) {
    l_fatal_assert(allocator != nullptr);
    return allocator->allocate(n * sizeof(T), gea_alignof(T));
}

template <class T>
inline void deallocate_object(allocator *allocator, void *p, const size_t &n) {
    l_fatal_assert(allocator != nullptr);
    return allocator->deallocate(p);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
