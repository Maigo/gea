
namespace gea {

// ------------------------------------------------------------------------- //
// basic_string                                                              //
// ------------------------------------------------------------------------- //
// constructor
template <typename C, typename A>
inline basic_string<C,A>::basic_string()
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(NULL) {
    allocate_self();
}
template <typename C, typename A>
inline basic_string<C,A>::basic_string(const this_type &o)
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(o.mp_allocator) {
    range_initialize(o.mp_begin, o.mp_end);
}
template <typename C, typename A>
inline basic_string<C,A>::basic_string(const this_type &o, size_type position, size_type n)
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(o.mp_allocator) {
    range_initialize(o.mp_begin + position, o.mp_begin + position + mth::min(n, o.size() - position));
}
template <typename C, typename A>
inline basic_string<C,A>::basic_string(const value_type *p)
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(NULL) {
    range_initialize(p);
}
template <typename C, typename A>
inline basic_string<C,A>::basic_string(const value_type *p, size_type n)
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(NULL) {
    range_initialize(p, p + n);
}
template <typename C, typename A>
inline basic_string<C,A>::basic_string(size_type n, letter_type c)
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(NULL) {
    size_initialize(n, c);
}
template <typename C, typename A>
inline basic_string<C,A>::basic_string(const value_type *p_begin, const value_type *p_end)
: mp_begin(NULL), mp_end(NULL), mp_capacity(NULL), mp_allocator(NULL) {
    range_initialize(p_begin, p_end);
}
template <typename C, typename A>
inline basic_string<C,A>::~basic_string() {
    deallocate_self();
}

// attribute
template <typename C, typename A>
bool basic_string<C,A>::empty() const { return size() == 0; }
template <typename C, typename A>
const typename basic_string<C,A>::size_type basic_string<C,A>::size() const {
    return (size_type)(mp_end - mp_begin);
}
template <typename C, typename A>
const typename basic_string<C,A>::size_type basic_string<C,A>::length() const {
    return charset_type::length(mp_begin, mp_end);
}
template <typename C, typename A>
const typename basic_string<C,A>::size_type basic_string<C,A>::max_size() const {
    return k_max_size;
}
template <typename C, typename A>
const typename basic_string<C,A>::size_type basic_string<C,A>::capacity() const {
    return (size_type)(mp_capacity - mp_begin);
}

// private helper functions
template <typename C, typename A>
inline typename basic_string<C,A>::value_type *basic_string<C,A>::do_allocate(size_type n) {
//    l_assert_msg(n > 1, "invalid allocation size!")
    return (value_type *) malloc(n * sizeof(value_type));
}
template <typename C, typename A>
inline void basic_string<C,A>::do_free(value_type *p, size_type n) {
    if (p != NULL)
        free(p);
}
template <typename C, typename A>
inline typename basic_string<C,A>::size_type basic_string<C,A>::get_new_capacity(size_type current_capacity) {
    return (current_capacity > initial_capacity) ? (2 * current_capacity) : initial_capacity;
}

template <typename C, typename A>
inline void basic_string<C,A>::allocate_self() {
//    l_assert_msg(g_empty_string.mUint32 == 0);
    mp_begin     = const_cast<value_type *>(get_empty_string<value_type>());
    mp_end       = mp_begin;
    mp_capacity  = mp_begin + 1;
}
template <typename C, typename A>
inline void basic_string<C,A>::allocate_self(size_type n) {
    if(n > 1) {
        mp_begin    = do_allocate(n);
        mp_end      = mp_begin;
        mp_capacity = mp_begin + n;
    } else
        allocate_self();
}
template <typename C, typename A>
inline void basic_string<C,A>::deallocate_self() {
    const size_type capacity = (size_type)(mp_capacity - mp_begin);
    if(capacity > 1)
        do_free(mp_begin, capacity);
}
template <typename C, typename A>
inline void basic_string<C,A>::range_initialize(const value_type *p_begin, const value_type *p_end) {
    const size_type n = (size_type)(p_end - p_begin);

    allocate_self(n + charset_type::size_null);

    mp_end = charset_type::uninitialized_copy(p_begin, p_end, mp_begin);
    charset_type::null_terminate(mp_end);
}
template <typename C, typename A>
inline void basic_string<C,A>::range_initialize(const value_type *p_begin) {
    const size_type n = charset_type::size(p_begin);
    range_initialize(p_begin, p_begin + n);    
}
template <typename C, typename A>
inline void basic_string<C,A>::size_initialize(size_type n, letter_type c) {
    allocate_self(charset_type::size(c) * n + charset_type::size_null);

    mp_end = charset_type::uninitialized_fill_n(mp_begin, n, c);
    charset_type::null_terminate(mp_end);
}

} // namespace gea //
