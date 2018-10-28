#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// allocator                                                                 //
// ------------------------------------------------------------------------- //
class allocator {
public:
    virtual void *allocate(size_t size, size_t align) = 0;
    virtual void deallocate(void *p) = 0;
    virtual size_t allocated_size(const void *p) = 0;

    template <class T, typename ... Args> inline T *make_new(Args ... args);

    template <class T> inline void make_delete(T *p);
};

// ------------------------------------------------------------------------- //
//                                                                           //
// ------------------------------------------------------------------------- //
inline void *allocate_memory(allocator *allocator, const size_t &size, const size_t &align);
inline void deallocate_memory(allocator *allocator, void *p, const size_t &size);

template <class T>
inline void *allocate_object(allocator *allocator, const size_t &n = 1);

template <class T>
inline void deallocate_object(allocator *allocator, void *p, const size_t &n = 1);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "allocator.inl"
