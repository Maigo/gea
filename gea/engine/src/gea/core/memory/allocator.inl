
namespace gea {

// ------------------------------------------------------------------------- //
// allocator                                                                 //
// ------------------------------------------------------------------------- //
template <class T>
inline T *allocator::make_new() {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T();
}
template <class T, class Arg0>
inline T *allocator::make_new(const Arg0 &arg0) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0);
}
template <class T, class Arg0, class Arg1>
inline T *allocator::make_new(const Arg0 &arg0, const Arg1 &arg1) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0, arg1);
}
template <class T, class Arg0, class Arg1, class Arg2>
inline T *allocator::make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0, arg1, arg2);
}
template <class T, class Arg0, class Arg1, class Arg2, class Arg3>
inline T *allocator::make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0, arg1, arg2, arg3);
}
template <class T, class Arg0, class Arg1, class Arg2, class Arg3, class Arg4>
inline T *allocator::make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0, arg1, arg2, arg3, arg4);
}
template <class T, class Arg0, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline T *allocator::make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0, arg1, arg2, arg3, arg4, arg5);
}
template <class T, class Arg0, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline T *allocator::make_new(const Arg0 &arg0, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5, const Arg6 &arg6) {
    return new (allocate(gea_sizeof(T), gea_alignof(T))) T(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
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
inline void *allocate_memory(allocator *a, const size_t &size, const size_t &align) {
    return a->allocate(size, align);
}
inline void deallocate_memory(allocator *a, void *p, const size_t &size) {
    a->deallocate(p);
}

template <class T>
inline void *allocate_object(allocator *a, const size_t &n) {
    return a->allocate(n * gea_sizeof(T), gea_alignof(T));
}

template <class T>
inline void deallocate_object(allocator *a, void *p, const size_t &n) {
    return a->deallocate(p);
}

} // namespace gea //
