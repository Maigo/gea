#ifndef __UNI_STRING_H__
#define __UNI_STRING_H__

namespace gea {

#define alignof __alignof

namespace mth {
//TODO: move
template <typename T>
inline const T &min(const T &a, const T &b) { return (a > b) ? b : a; }
} // namespace mth //

static const uint32_t gk_empty_string = 0;

template <typename T>
inline const T * get_empty_string() { return (T *) &gk_empty_string; }

// ------------------------------------------------------------------------- //
// basic_string                                                              //
// ------------------------------------------------------------------------- //
template <typename C, typename A>
class basic_string {
public:
    // type definitions
    typedef basic_string<C,A> this_type;
    typedef C                 charset_type;
    typedef A                 allocator_type;

    typedef typename C::value_type  value_type;
    typedef typename C::size_type   size_type;
    typedef typename C::letter_type letter_type;

    // constants
    static const size_type k_npos      = (size_type)-1;
    static const size_type k_max_size  = (size_type)-2;
    static const size_type k_alignment = alignof(value_type);
    static const size_type k_alignment_offset = 0;

    // constructor
    inline basic_string();
    inline explicit basic_string(const this_type &o);
    inline basic_string(const this_type &o, size_type position, size_type n = k_npos);
    inline explicit basic_string(const value_type *p);
    inline basic_string(const value_type *p, size_type n);
    inline basic_string(size_type n, letter_type c);
    inline basic_string(const value_type *p_begin, const value_type *p_end);
    inline ~basic_string();

    //// allocator
    //      allocator_type *get_allocator();
    //const allocator_type *get_allocator() const;
    //void                  set_allocator(allocator_type *allocator);

    //// assignment
    //this_type &operator =(const this_type &o);
    //this_type &operator =(const value_type *p);
    //this_type &operator =(letter_type c);

    //void swap(this_type &x);

    //// modifiers
    //void resize(size_type n, letter_type c);
    //void resize(size_type n);
    //void reserve(size_type = 0);
    //void set_capacity(size_type n = k_npos);
    //void force_size(size_type n);

    // attribute
    bool            empty() const;
    const size_type size() const;
    const size_type length() const;
    const size_type max_size() const;
    const size_type capacity() const;

    //// member access
    //      letter_type operator[](size_type idx);
    //const letter_type operator[](size_type idx) const;
    //      letter_type at(size_type idx);
    //const letter_type at(size_type idx) const;

private:
    static const size_type initial_capacity = 8;

    // private helper functions
    inline value_type *do_allocate(size_type n);
    inline void        do_free(value_type* p, size_type n);
    inline size_type   get_new_capacity(size_type current_capacity);

    inline void        allocate_self();
    inline void        allocate_self(size_type n);
    inline void        deallocate_self();
    inline void        range_initialize(const value_type *p_begin, const value_type *p_end);
    inline void        range_initialize(const value_type *p_begin);
    inline void        size_initialize(size_type n, letter_type c);

    value_type     *mp_begin;
    value_type     *mp_end;
    value_type     *mp_capacity;
    allocator_type *mp_allocator;
};

} // namespace gea //

#include "string.inl"

#endif // __UNI_STRING_H__ //
