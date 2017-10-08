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

    template <class T> inline T *make_new();
    template <class T, class Arg0> inline T *make_new(const Arg0 &arg0);
    template <class T, class Arg0, class Arg1> inline T *make_new(const Arg0 &arg0, const Arg1 &arg1);
    template <class T, class Arg0, class Arg1, class Arg2> inline T *make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2);
    template <class T, class Arg0, class Arg1, class Arg2, class Arg3> inline T *make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
    template <class T, class Arg0, class Arg1, class Arg2, class Arg3, class Arg4> inline T *make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
    template <class T, class Arg0, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5> inline T *make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);
    template <class T, class Arg0, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6> inline T *make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5, const Arg6 &arg6);

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
