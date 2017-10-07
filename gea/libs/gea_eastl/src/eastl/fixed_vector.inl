namespace gea {

template <typename T, size_t N>
inline fixed_vector<T, N>::fixed_vector()
    : base_type(fixed_allocator_type(m_buffer.buffer))
{
//#if EASTL_NAME_ENABLED
//    mAllocator.set_name(EASTL_FIXED_VECTOR_DEFAULT_NAME);
//#endif

    mp_begin = mp_end = (value_type*) &m_buffer.buffer[0];
    mp_capacity = mp_begin + N;
}

template <typename T, size_t N>
inline fixed_vector<T, N>::fixed_vector(size_type n)
    : base_type(fixed_allocator_type(m_buffer.buffer))
{
//#if EASTL_NAME_ENABLED
//    mAllocator.set_name(EASTL_FIXED_VECTOR_DEFAULT_NAME);
//#endif

    mp_begin = mp_end = (value_type*) &m_buffer.buffer[0];
    mp_capacity = mp_begin + N;
    resize(n);
}

template <typename T, size_t N>
inline fixed_vector<T, N>::fixed_vector(size_type n, const value_type& value)
    : base_type(fixed_allocator_type(m_buffer.buffer))
{
//#if EASTL_NAME_ENABLED
//    mAllocator.set_name(EASTL_FIXED_VECTOR_DEFAULT_NAME);
//#endif

    mp_begin = mp_end = (value_type*) &m_buffer.buffer[0];
    mp_capacity = mp_begin + N;
    resize(n, value);
}

template <typename T, size_t N>
inline fixed_vector<T, N>::fixed_vector(const this_type& x)
    : base_type(fixed_allocator_type(m_buffer.buffer))
{
//#if EASTL_NAME_ENABLED
//    mAllocator.set_name(x.mAllocator.get_name());
//#endif

    mp_begin = mp_end = (value_type*)&m_buffer.buffer[0];
    mp_capacity = mp_begin + N;
    base_type::template do_assign<const_iterator, false>(x.begin(), x.end(), false_type());
}

template <typename T, size_t N>
template <typename input_iterator>
fixed_vector<T, N>::fixed_vector(input_iterator first, input_iterator last)
    : base_type(fixed_allocator_type(m_buffer.buffer))
{
//#if EASTL_NAME_ENABLED
//    mAllocator.set_name(EASTL_FIXED_VECTOR_DEFAULT_NAME);
//#endif

    mp_begin = mp_end = (value_type*)&m_buffer.buffer[0];
    mp_capacity = mp_begin + N;
    base_type::template do_assign<input_iterator, false>(first, last, is_integral<input_iterator>());
}

template <typename T, size_t N>
inline typename fixed_vector<T, N>::this_type&
fixed_vector<T, N>::operator=(const this_type& x)
{
    if (this != &x)
    {
        clear();

        base_type::template do_assign<const_iterator, false>(x.begin(), x.end(), false_type()); // Shorter route.
    }
    return *this;
}

template <typename T, size_t N>
inline void fixed_vector<T, N>::swap(this_type& x)
{
    // Fixed containers use a special swap that can deal with excessively large buffers.
    eastl::fixed_swap(*this, x);
}

template <typename T, size_t N>
inline void fixed_vector<T, N>::set_capacity(size_type n)
{
    const size_type n_prev_size = (size_type)(mp_end - mp_begin);
    const size_type n_prev_capacity = (size_type)(mp_capacity - mp_begin);

    if (n == npos)       // If the user means to set the capacity so that it equals the size (i.e. free excess capacity)...
        n = n_prev_size;

    if (n != n_prev_capacity)  // If the request results in a capacity change...
    {
        if (n > k_max_size))
        {
            // TODO: assert
        } // Else the new capacity would be within our fixed buffer.
        else if (n < n_prev_size) // If the newly requested capacity is less than our size, we do what vector::set_capacity does and resize, even though we actually aren't reducing the capacity.
            resize(n);
    }
}

template <typename T, size_t N>
inline void fixed_vector<T, N>::clear()
{
    base_type::clear();
}

template <typename T, size_t N>
inline void fixed_vector<T, N>::reset_lose_memory()
{
    mp_begin = mp_end = (value_type*)&m_buffer.buffer[0];
    mp_capacity = mp_begin + N;
}

template <typename T, size_t N>
inline typename fixed_vector<T, N>::size_type
fixed_vector<T, N>::max_size() const
{
    return k_max_size;
}

template <typename T, size_t N>
inline bool fixed_vector<T, N>::full() const
{
    // If size >= capacity, then we are definitely full. 
    return ((size_t)(mp_end - mp_begin) >= k_max_size);
}

template <typename T, size_t N>
inline void* fixed_vector<T, N>::push_back_uninitialized()
{
    return do_push_back_uninitialized(false_type());
}

template <typename T, size_t N>
inline void* fixed_vector<T, N>::do_push_back_uninitialized()
{
//    EASTL_ASSERT(mp_end < mp_capacity);

    return mp_end++;
}

template <typename T, size_t N>
inline void fixed_vector<T, N>::push_back(const value_type& value)
{
    do_push_back(false_type(), value);
}

// This template specializes for overflow NOT enabled.
// In this configuration, there is no need for the heavy weight push_back() which tests to see if the container should grow (it never will)
template <typename T, size_t N>
inline void fixed_vector<T, N>::do_push_back(const value_type& value)
{
//    EASTL_ASSERT(mp_end < mp_capacity);

    ::new((void*)mp_end++) value_type(value);
}

template <typename T, size_t N>
inline typename fixed_vector<T, N>::reference fixed_vector<T, N>::push_back()
{
    return do_push_back(false_type());
}

// This template specializes for overflow NOT enabled.
// In this configuration, there is no need for the heavy weight push_back() which tests to see if the container should grow (it never will)
template <typename T, size_t N>
inline typename fixed_vector<T, N>::reference fixed_vector<T, N>::do_push_back()
{
//    EASTL_ASSERT(mp_end < mp_capacity);

    ::new((void*)mp_end++) value_type;    // Note that this isn't value_type() as that syntax doesn't work on all compilers for POD types.

    return *(mp_end - 1);        // Same as return back();
}

///////////////////////////////////////////////////////////////////////
// global operators
///////////////////////////////////////////////////////////////////////

// operator ==, !=, <, >, <=, >= come from the vector implementations.

template <typename T, size_t N>
inline void swap(fixed_vector<T, N>& a, fixed_vector<T, N>& b)
{
    // Fixed containers use a special swap that can deal with excessively large buffers.
    eastl::fixed_swap(a, b);
}

} // namespace gea //
