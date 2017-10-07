namespace gea {

// ------------------------------------------------------------------------- //
// vector_base                                                               //
// ------------------------------------------------------------------------- //

template <typename T, typename allocator>
inline vector_base<T, allocator>::vector_base(const allocator_type& allocator)
    : mp_begin(NULL)
    , mp_end(NULL)
    , mp_capacity(NULL)
    , m_allocator(allocator)
{
}

template <typename T, typename allocator>
inline vector_base<T, allocator>::vector_base(size_type n, const allocator_type& allocator)
    : m_allocator(allocator)
{
    mp_begin = do_allocate(n);
    mp_end = mp_begin;
    mp_capacity = mp_begin + n;
}

template <typename T, typename allocator>
inline vector_base<T, allocator>::~vector_base()
{
    if (mp_begin) {
        EASTLFree(m_allocator, mp_begin, (mp_capacity - mp_begin) * sizeof(T));
    }
}

template <typename T, typename allocator>
inline const typename vector_base<T, allocator>::allocator_type& vector_base<T, allocator>::get_allocator() const GEA_NOEXCEPT
{
    return m_allocator;
}

template <typename T, typename allocator>
inline typename vector_base<T, allocator>::allocator_type& vector_base<T, allocator>::get_allocator() GEA_NOEXCEPT
{
    return m_allocator;
}

template <typename T, typename allocator>
inline void vector_base<T, allocator>::set_allocator(const allocator_type& allocator)
{
    m_allocator = allocator;
}

template <typename T, typename allocator>
inline T* vector_base<T, allocator>::do_allocate(size_type n)
{
#if GEA_ASSERT_ENABLED
    if (GEA_UNLIKELY(n >= 0x80000000))
        GEA_FAIL_DESC("vector::do_allocate -- improbably large request.");
#endif

    // If n is zero, then we allocate no memory and just return NULL. 
    // This is fine, as our default ctor initializes with NULL pointers. 
    return n ? (T*) allocate_memory(m_allocator, n * sizeof(T), GEA_ALIGN_OF(T), 0) : nullptr;
}

template <typename T, typename allocator>
inline void vector_base<T, allocator>::do_free(T* p, size_type n)
{
    if (p) {
        EASTLFree(m_allocator, p, n * sizeof(T));
    }
}

template <typename T, typename allocator>
inline typename vector_base<T, allocator>::size_type vector_base<T, allocator>::get_new_capacity(size_type current_capacity)
{
    // This needs to return a value of at least current_capacity and at least 1.
    return (current_capacity > 0) ? (2 * current_capacity) : 1;
}

// ------------------------------------------------------------------------- //
// vector                                                                    //
// ------------------------------------------------------------------------- //

template <typename T, typename allocator>
inline vector<T, allocator>::vector(const allocator_type& allocator)
    : base_type(allocator)
{
}

template <typename T, typename allocator>
inline vector<T, allocator>::vector(size_type n, const allocator_type& allocator)
    : base_type(n, allocator)
{
    eastl::uninitialized_default_fill_n(mp_begin, n);
    mp_end = mp_begin + n;
}

template <typename T, typename allocator>
inline vector<T, allocator>::vector(size_type n, const value_type& value, const allocator_type& allocator)
    : base_type(n, allocator)
{
    eastl::uninitialized_fill_n_ptr(mp_begin, n, value);
    mp_end = mp_begin + n;
}

template <typename T, typename allocator>
inline vector<T, allocator>::vector(const this_type& x)
    : base_type(x.size(), x.m_allocator)
{
    mp_end = eastl::uninitialized_copy_ptr(x.mp_begin, x.mp_end, mp_begin);
}

template <typename T, typename allocator>
inline vector<T, allocator>::vector(const this_type& x, const allocator_type& allocator)
    : base_type(x.size(), allocator)
{
    mp_end = eastl::uninitialized_copy_ptr(x.mp_begin, x.mp_end, mp_begin);
}

//#if EASTL_MOVE_SEMANTICS_ENABLED
//template <typename T, typename allocator>
//inline vector<T, allocator>::vector(this_type&& x)
//    : base_type(x.m_allocator)
//{
//    DoSwap(x);
//}
//
//template <typename T, typename allocator>
//inline vector<T, allocator>::vector(this_type&& x, const allocator_type& allocator)
//    : base_type(allocator)
//{
//    swap(x); // member swap handles the case that x has a different allocator than our allocator by doing a copy.
//}
//#endif

//template <typename T, typename allocator>
//inline vector<T, allocator>::vector(std::initializer_list<value_type> ilist, const allocator_type& allocator)
//    : base_type(allocator)
//{
//    do_init(ilist.begin(), ilist.end(), false_type());
//}

template <typename T, typename allocator>
template <typename input_iterator>
inline vector<T, allocator>::vector(input_iterator first, input_iterator last, const allocator_type& allocator)
    : base_type(allocator)
{
    do_init(first, last, is_integral<input_iterator>());
}

template <typename T, typename allocator>
inline vector<T, allocator>::~vector()
{
    // Call destructor for the values. Parent class will free the memory.
    eastl::destruct(mp_begin, mp_end);
}

template <typename T, typename allocator>
typename vector<T, allocator>::this_type& vector<T, allocator>::operator=(const this_type& x)
{
    if (this != &x) // If not assigning to self...
    {
        do_assign<const_iterator, false>(x.begin(), x.end(), eastl::false_type());
    }

    return *this;
}

//template <typename T, typename allocator>
//typename vector<T, allocator>::this_type& vector<T, allocator>::operator=(std::initializer_list<value_type> ilist)
//{
//    typedef typename std::initializer_list<value_type>::iterator input_iterator;
//    typedef typename eastl::iterator_traits<input_iterator>::iterator_category IC;
//    do_assign_from_iterator<input_iterator, false>(ilist.begin(), ilist.end(), IC()); // initializer_list has const elements and so we can't move from them.
//    return *this;
//}

//#if EASTL_MOVE_SEMANTICS_ENABLED
//template <typename T, typename allocator>
//typename vector<T, allocator>::this_type& vector<T, allocator>::operator=(this_type&& x)
//{
//    if (this != &x)
//    {
//        do_clear_capacity(); // To consider: Are we really required to clear here? x is going away soon and will clear itself in its dtor.
//        swap(x);             // member swap handles the case that x has a different allocator than our allocator by doing a copy.
//    }
//    return *this;
//}
//#endif

template <typename T, typename allocator>
inline void vector<T, allocator>::assign(size_type n, const value_type& value)
{
    do_assign_values(n, value);
}

template <typename T, typename allocator>
template <typename input_iterator>
inline void vector<T, allocator>::assign(input_iterator first, input_iterator last)
{
    // It turns out that the C++ std::vector<int, int> specifies a two argument
    // version of assign that takes (int size, int value). These are not iterators, 
    // so we need to do a template compiler trick to do the right thing.
    do_assign<input_iterator, false>(first, last, is_integral<input_iterator>());
}

template <typename T, typename allocator>
inline void vector<T, allocator>::assign(std::initializer_list<value_type> ilist)
{
    typedef typename std::initializer_list<value_type>::iterator input_iterator;
    typedef typename eastl::iterator_traits<input_iterator>::iterator_category IC;
    do_assign_from_iterator<input_iterator, false>(ilist.begin(), ilist.end(), IC()); // initializer_list has const elements and so we can't move from them.
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::begin() GEA_NOEXCEPT
{
    return mp_begin;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_iterator
    vector<T, allocator>::begin() const GEA_NOEXCEPT
{
    return mp_begin;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_iterator
    vector<T, allocator>::cbegin() const GEA_NOEXCEPT
{
    return mp_begin;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::end() GEA_NOEXCEPT
{
    return mp_end;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_iterator
    vector<T, allocator>::end() const GEA_NOEXCEPT
{
    return mp_end;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_iterator
    vector<T, allocator>::cend() const GEA_NOEXCEPT
{
    return mp_end;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::reverse_iterator
    vector<T, allocator>::rbegin() GEA_NOEXCEPT
{
    return reverse_iterator(mp_end);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reverse_iterator
    vector<T, allocator>::rbegin() const GEA_NOEXCEPT
{
    return const_reverse_iterator(mp_end);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reverse_iterator
    vector<T, allocator>::crbegin() const GEA_NOEXCEPT
{
    return const_reverse_iterator(mp_end);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::reverse_iterator
    vector<T, allocator>::rend() GEA_NOEXCEPT
{
    return reverse_iterator(mp_begin);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reverse_iterator
    vector<T, allocator>::rend() const GEA_NOEXCEPT
{
    return const_reverse_iterator(mp_begin);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reverse_iterator
    vector<T, allocator>::crend() const GEA_NOEXCEPT
{
    return const_reverse_iterator(mp_begin);
}

    template <typename T, typename allocator>
bool vector<T, allocator>::empty() const GEA_NOEXCEPT
{
    return (mp_begin == mp_end);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::size_type
    vector<T, allocator>::size() const GEA_NOEXCEPT
{
    return (size_type)(mp_end - mp_begin);
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::size_type
    vector<T, allocator>::capacity() const GEA_NOEXCEPT
{
    return (size_type)(mp_capacity - mp_begin);
}

    template <typename T, typename allocator>
inline void vector<T, allocator>::resize(size_type n, const value_type& value)
{
    if (n > (size_type)(mp_end - mp_begin))  // We expect that more often than not, resizes will be upsizes.
        DoInsertValuesEnd(n - ((size_type)(mp_end - mp_begin)), value);
    else
    {
        eastl::destruct(mp_begin + n, mp_end);
        mp_end = mp_begin + n;
    }
}

template <typename T, typename allocator>
inline void vector<T, allocator>::resize(size_type n)
{
    // Alternative implementation:
    // resize(n, value_type());

    if (n > (size_type)(mp_end - mp_begin))  // We expect that more often than not, resizes will be upsizes.
        DoInsertValuesEnd(n - ((size_type)(mp_end - mp_begin)));
    else
    {
        eastl::destruct(mp_begin + n, mp_end);
        mp_end = mp_begin + n;
    }
}

template <typename T, typename allocator>
void vector<T, allocator>::reserve(size_type n)
{
    // If the user wants to reduce the reserved memory, there is the set_capacity function.
    if (n > size_type(mp_capacity - mp_begin)) // If n > capacity ...
        DoGrow(n);
}

template <typename T, typename allocator>
void vector<T, allocator>::set_capacity(size_type n)
{
    if ((n == npos) || (n <= (size_type)(mp_end - mp_begin))) // If new capacity <= size...
    {
        if (n == 0)  // Very often n will be 0, and clear will be faster than resize and use less stack space.
            clear();
        else if (n < (size_type)(mp_end - mp_begin))
            resize(n);

        this_type temp(*this);  // This is the simplest way to accomplish this, 
        swap(temp);             // and it is as efficient as any other.
    }
    else // Else new capacity > size.
    {
        pointer const pNewData = DoRealloc(n, mp_begin, mp_end, should_move_tag());
        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        const ptrdiff_t nPrevSize = mp_end - mp_begin;
        mp_begin = pNewData;
        mp_end = pNewData + nPrevSize;
        mp_capacity = mp_begin + n;
    }
}

template <typename T, typename allocator>
inline void vector<T, allocator>::shrink_to_fit()
{
    // This is the simplest way to accomplish this, and it is as efficient as any other.

#if EASTL_MOVE_SEMANTICS_ENABLED
    this_type temp = this_type(move_iterator<iterator>(begin()), move_iterator<iterator>(end()), m_allocator);
#else
    this_type temp(*this);
#endif
    // Call DoSwap() rather than swap() as we know our allocators match and we don't want to invoke the code path
    // handling non matching allocators as it imposes additional restrictions on the type of T to be copyable
    DoSwap(temp);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::pointer
    vector<T, allocator>::data() GEA_NOEXCEPT
{
    return mp_begin;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::const_pointer
    vector<T, allocator>::data() const GEA_NOEXCEPT
{
    return mp_begin;
}

    template <typename T, typename allocator>
inline typename vector<T, allocator>::reference
    vector<T, allocator>::operator[](size_type n)
{
#if EASTL_EMPTY_REFERENCE_ASSERT_ENABLED    // We allow the user to use a reference to v[0] of an empty container. But this was merely grandfathered in and ideally we shouldn't allow such access to [0].
    if (EASTL_UNLIKELY((n != 0) && (n >= (static_cast<size_type>(mp_end - mp_begin)))))
        EASTL_FAIL_MSG("vector::operator[] -- out of range");
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(n >= (static_cast<size_type>(mp_end - mp_begin))))
        EASTL_FAIL_MSG("vector::operator[] -- out of range");
#endif

    return *(mp_begin + n);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reference
    vector<T, allocator>::operator[](size_type n) const
{
#if EASTL_EMPTY_REFERENCE_ASSERT_ENABLED    // We allow the user to use a reference to v[0] of an empty container. But this was merely grandfathered in and ideally we shouldn't allow such access to [0].
    if (EASTL_UNLIKELY((n != 0) && (n >= (static_cast<size_type>(mp_end - mp_begin)))))
        EASTL_FAIL_MSG("vector::operator[] -- out of range");
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(n >= (static_cast<size_type>(mp_end - mp_begin))))
        EASTL_FAIL_MSG("vector::operator[] -- out of range");
#endif

    return *(mp_begin + n);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::reference
    vector<T, allocator>::at(size_type n)
{
    // The difference between at and operator[] is that at signals 
    // if the requested position is out of range by throwing an 
    // out_of_range exception.

#if EASTL_EXCEPTIONS_ENABLED
    if (EASTL_UNLIKELY(n >= (static_cast<size_type>(mp_end - mp_begin))))
        throw std::out_of_range("vector::at -- out of range");
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(n >= (static_cast<size_type>(mp_end - mp_begin))))
        EASTL_FAIL_MSG("vector::at -- out of range");
#endif

    return *(mp_begin + n);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reference
    vector<T, allocator>::at(size_type n) const
{
#if EASTL_EXCEPTIONS_ENABLED
    if (EASTL_UNLIKELY(n >= (static_cast<size_type>(mp_end - mp_begin))))
        throw std::out_of_range("vector::at -- out of range");
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(n >= (static_cast<size_type>(mp_end - mp_begin))))
        EASTL_FAIL_MSG("vector::at -- out of range");
#endif

    return *(mp_begin + n);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::reference
    vector<T, allocator>::front()
{
#if EASTL_EMPTY_REFERENCE_ASSERT_ENABLED
    // We allow the user to reference an empty container.
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(mp_end <= mp_begin)) // We don't allow the user to reference an empty container.
        EASTL_FAIL_MSG("vector::front -- empty vector");
#endif

    return *mp_begin;
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reference
    vector<T, allocator>::front() const
{
#if EASTL_EMPTY_REFERENCE_ASSERT_ENABLED
    // We allow the user to reference an empty container.
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(mp_end <= mp_begin)) // We don't allow the user to reference an empty container.
        EASTL_FAIL_MSG("vector::front -- empty vector");
#endif

    return *mp_begin;
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::reference
    vector<T, allocator>::back()
{
#if EASTL_EMPTY_REFERENCE_ASSERT_ENABLED
    // We allow the user to reference an empty container.
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(mp_end <= mp_begin)) // We don't allow the user to reference an empty container.
        EASTL_FAIL_MSG("vector::back -- empty vector");
#endif

    return *(mp_end - 1);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::const_reference
    vector<T, allocator>::back() const
{
#if EASTL_EMPTY_REFERENCE_ASSERT_ENABLED
    // We allow the user to reference an empty container.
#elif EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(mp_end <= mp_begin)) // We don't allow the user to reference an empty container.
        EASTL_FAIL_MSG("vector::back -- empty vector");
#endif

    return *(mp_end - 1);
}

template <typename T, typename allocator>
inline void vector<T, allocator>::push_back(const value_type& value)
{
    if (mp_end < mp_capacity)
        ::new((void*)mp_end++) value_type(value);
    else
        DoInsertValueEnd(value);
}

#if EASTL_MOVE_SEMANTICS_ENABLED
template <typename T, typename allocator>
inline void vector<T, allocator>::push_back(value_type&& value)
{
    if (mp_end < mp_capacity)
        ::new((void*)mp_end++) value_type(eastl::move(value));
    else
        DoInsertValueEnd(eastl::move(value));
}
#endif

template <typename T, typename allocator>
inline typename vector<T, allocator>::reference
    vector<T, allocator>::push_back()
{
    if (mp_end < mp_capacity)
        ::new((void*)mp_end++) value_type();
    else // Note that in this case we create a temporary, which is less desirable.
        DoInsertValueEnd(value_type());

    return *(mp_end - 1); // Same as return back();
}

template <typename T, typename allocator>
inline void* vector<T, allocator>::push_back_uninitialized()
{
    if (mp_end == mp_capacity)
    {
        const size_type newSize = (size_type)(mp_end - mp_begin) + 1;
        reserve(newSize);
    }

    return mp_end++;
}

template <typename T, typename allocator>
inline void vector<T, allocator>::pop_back()
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY(mp_end <= mp_begin))
        EASTL_FAIL_MSG("vector::pop_back -- empty vector");
#endif

    --mp_end;
    mp_end->~value_type();
}

#if EASTL_MOVE_SEMANTICS_ENABLED && EASTL_VARIADIC_TEMPLATES_ENABLED
template <typename T, typename allocator>
template<class... Args>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::emplace(const_iterator position, Args&&... args)
{
    const ptrdiff_t n = position - mp_begin; // Save this because we might reallocate.

    if ((mp_end == mp_capacity) || (position != mp_end))
        DoInsertValue(position, eastl::forward<Args>(args)...);
    else
    {
        ::new((void*)mp_end) value_type(eastl::forward<Args>(args)...);
        ++mp_end; // Increment this after the construction above in case the construction throws an exception.
    }

    return mp_begin + n;
}

template <typename T, typename allocator>
template<class... Args>
inline void vector<T, allocator>::emplace_back(Args&&... args)
{
    if (mp_end < mp_capacity)
    {
        ::new((void*)mp_end) value_type(eastl::forward<Args>(args)...);  // If value_type has a move constructor, it will use it and this operation may be faster than otherwise.
        ++mp_end; // Increment this after the construction above in case the construction throws an exception.
    }
    else
        DoInsertValueEnd(eastl::forward<Args>(args)...);
}
#else
#if EASTL_MOVE_SEMANTICS_ENABLED
template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::emplace(const_iterator position, value_type&& value)
{
    const ptrdiff_t n = position - mp_begin; // Save this because we might reallocate.

    if ((mp_end == mp_capacity) || (position != mp_end))
        DoInsertValue(position, eastl::move(value));
    else
    {
        ::new((void*)mp_end) value_type(eastl::move(value));
        ++mp_end; // Increment this after the construction above in case the construction throws an exception.
    }

    return mp_begin + n;
}

template <typename T, typename allocator>
inline void vector<T, allocator>::emplace_back(value_type&& value)
{
    if (mp_end < mp_capacity)
    {
        ::new((void*)mp_end) value_type(eastl::move(value));  // If value_type has a move constructor, it will use it and this operation may be faster than otherwise.
        ++mp_end; // Increment this after the construction above in case the construction throws an exception.
    }
    else
        DoInsertValueEnd(eastl::move(value));
}
#endif

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::emplace(const_iterator position, const value_type& value)
{
    return insert(position, value);
}

template <typename T, typename allocator>
inline void vector<T, allocator>::emplace_back(const value_type& value)
{
    push_back(value);
}
#endif

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::insert(const_iterator position, const value_type& value)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position > mp_end)))
        EASTL_FAIL_MSG("vector::insert -- invalid position");
#endif

    // We implment a quick pathway for the case that the insertion position is at the end and we have free capacity for it.
    const ptrdiff_t n = position - mp_begin; // Save this because we might reallocate.

    if ((mp_end == mp_capacity) || (position != mp_end))
        DoInsertValue(position, value);
    else
    {
        ::new((void*)mp_end) value_type(value);
        ++mp_end; // Increment this after the construction above in case the construction throws an exception.
    }

    return mp_begin + n;
}

#if EASTL_MOVE_SEMANTICS_ENABLED
template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::insert(const_iterator position, value_type&& value)
{
    return emplace(position, eastl::move(value));
}
#endif

template <typename T, typename allocator>
inline void vector<T, allocator>::insert(const_iterator position, size_type n, const value_type& value)
{
    DoInsertValues(position, n, value);
}

template <typename T, typename allocator>
template <typename input_iterator>
inline void vector<T, allocator>::insert(const_iterator position, input_iterator first, input_iterator last)
{
    DoInsert(position, first, last, is_integral<input_iterator>());
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::insert(const_iterator position, std::initializer_list<value_type> ilist)
{
    const ptrdiff_t n = position - mp_begin; // Save this because we might reallocate.
    DoInsert(position, ilist.begin(), ilist.end(), false_type());
    return mp_begin + n;
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::erase(const_iterator position)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position >= mp_end)))
        EASTL_FAIL_MSG("vector::erase -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);

    if ((position + 1) < mp_end)
        eastl::move(destPosition + 1, mp_end, destPosition);
    --mp_end;
    mp_end->~value_type();
    return destPosition;
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::erase(const_iterator first, const_iterator last)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((first < mp_begin) || (first > mp_end) || (last < mp_begin) || (last > mp_end) || (last < first)))
        EASTL_FAIL_MSG("vector::erase -- invalid position");
#endif

    iterator const position = const_cast<value_type*>(eastl::move(const_cast<value_type*>(last), const_cast<value_type*>(mp_end), const_cast<value_type*>(first)));
    eastl::destruct(position, mp_end);
    mp_end -= (last - first);

    return const_cast<value_type*>(first);
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::iterator
    vector<T, allocator>::erase_unsorted(const_iterator position)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position >= mp_end)))
        EASTL_FAIL_MSG("vector::erase -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);
    *destPosition = *(mp_end - 1);

    // pop_back();
    --mp_end;
    mp_end->~value_type();

    return destPosition;
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::reverse_iterator
    vector<T, allocator>::erase(const_reverse_iterator position)
{
    return reverse_iterator(erase((++position).base()));
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::reverse_iterator
    vector<T, allocator>::erase(const_reverse_iterator first, const_reverse_iterator last)
{
    // Version which erases in order from first to last.
    // difference_type i(first.base() - last.base());
    // while(i--)
    //     first = erase(first);
    // return first;

    // Version which erases in order from last to first, but is slightly more efficient:
    return reverse_iterator(erase(last.base(), first.base()));
}

template <typename T, typename allocator>
inline typename vector<T, allocator>::reverse_iterator
    vector<T, allocator>::erase_unsorted(const_reverse_iterator position)
{
    return reverse_iterator(erase_unsorted((++position).base()));
}

template <typename T, typename allocator>
inline void vector<T, allocator>::clear() GEA_NOEXCEPT
{
    eastl::destruct(mp_begin, mp_end);
    mp_end = mp_begin;
}

#if EASTL_RESET_ENABLED
    // This function name is deprecated; use reset_lose_memory instead.
    template <typename T, typename allocator>
inline void vector<T, allocator>::reset() GEA_NOEXCEPT
{
    reset_lose_memory();
}
#endif

    template <typename T, typename allocator>
inline void vector<T, allocator>::reset_lose_memory() GEA_NOEXCEPT
{
    // The reset function is a special extension function which unilaterally 
    // resets the container to an empty state without freeing the memory of 
    // the contained objects. This is useful for very quickly tearing down a 
    // container built into scratch memory.
    mp_begin = mp_end = mp_capacity = NULL;
}

    // swap exchanges the contents of two containers. With respect to the containers allocators,
    // the C11++ Standard (23.2.1/7) states that the behavior of a call to a container's swap function 
    // is undefined unless the objects being swapped have allocators that compare equal or 
    // allocator_traits<allocator_type>::propagate_on_container_swap::value is true (propagate_on_container_swap
    // is false by default). EASTL doesn't have allocator_traits and so this doesn't directly apply,
    // but EASTL has the effective behavior of propagate_on_container_swap = false for all allocators. 
    // So EASTL swap exchanges contents but not allocators, and swap is more efficient if allocators are equivalent.
    template <typename T, typename allocator>
inline void vector<T, allocator>::swap(this_type& x)
{
    if (m_allocator == x.m_allocator) // If allocators are equivalent...
        DoSwap(x);
    else // else swap the contents.
    {
        const this_type temp(*this); // Can't call eastl::swap because that would
        *this = x;                   // itself call this member swap function.
        x = temp;
    }
}

template <typename T, typename allocator>
template <typename ForwardIterator>
inline typename vector<T, allocator>::pointer
    vector<T, allocator>::DoRealloc(size_type n, ForwardIterator first, ForwardIterator last, should_copy_tag)
{
    T* const p = do_allocate(n); // p is of type T* but is not constructed. 
    eastl::uninitialized_copy_ptr(first, last, p); // copy-constructs p from [first,last).
    return p;
}

template <typename T, typename allocator>
template <typename ForwardIterator>
inline typename vector<T, allocator>::pointer
    vector<T, allocator>::DoRealloc(size_type n, ForwardIterator first, ForwardIterator last, should_move_tag)
{
    T* const p = do_allocate(n); // p is of type T* but is not constructed. 
    eastl::uninitialized_move_ptr_if_noexcept(first, last, p); // move-constructs p from [first,last).
    return p;
}

template <typename T, typename allocator>
template <typename Integer>
inline void vector<T, allocator>::do_init(Integer n, Integer value, true_type)
{
    mp_begin = do_allocate((size_type)n);
    mp_capacity = mp_begin + n;
    mp_end = mp_capacity;

    typedef typename eastl::remove_const<T>::type non_const_value_type; // If T is a const type (e.g. const int) then we need to initialize it as if it were non-const.
    eastl::uninitialized_fill_n_ptr<value_type, Integer>((non_const_value_type*)mp_begin, n, value);
}

template <typename T, typename allocator>
template <typename input_iterator>
inline void vector<T, allocator>::do_init(input_iterator first, input_iterator last, false_type)
{
    typedef typename eastl::iterator_traits<input_iterator>::iterator_category IC;
    do_initFromIterator(first, last, IC());
}

template <typename T, typename allocator>
template <typename input_iterator>
inline void vector<T, allocator>::do_initFromIterator(input_iterator first, input_iterator last, EASTL_ITC_NS::input_iterator_tag)
{
    // To do: Use emplace_back instead of push_back(). Our emplace_back will work below without any ifdefs.
    for (; first < last; ++first)  // input_iterators by definition actually only allow you to iterate through them once.
        push_back(*first);        // Thus the standard *requires* that we do this (inefficient) implementation.
}                                 // Luckily, input_iterators are in practice almost never used, so this code will likely never get executed.

template <typename T, typename allocator>
template <typename ForwardIterator>
inline void vector<T, allocator>::do_initFromIterator(ForwardIterator first, ForwardIterator last, EASTL_ITC_NS::forward_iterator_tag)
{
    const size_type n = (size_type)eastl::distance(first, last);
    mp_begin = do_allocate(n);
    mp_capacity = mp_begin + n;
    mp_end = mp_capacity;

    typedef typename eastl::remove_const<T>::type non_const_value_type; // If T is a const type (e.g. const int) then we need to initialize it as if it were non-const.
    eastl::uninitialized_copy_ptr(first, last, (non_const_value_type*)mp_begin);
}

template <typename T, typename allocator>
template <typename Integer, bool bMove>
inline void vector<T, allocator>::do_assign(Integer n, Integer value, true_type)
{
    do_assign_values(static_cast<size_type>(n), static_cast<value_type>(value));
}

template <typename T, typename allocator>
template <typename input_iterator, bool bMove>
inline void vector<T, allocator>::do_assign(input_iterator first, input_iterator last, false_type)
{
    typedef typename eastl::iterator_traits<input_iterator>::iterator_category IC;
    do_assign_from_iterator<input_iterator, bMove>(first, last, IC());
}

template <typename T, typename allocator>
void vector<T, allocator>::do_assign_values(size_type n, const value_type& value)
{
    if (n > size_type(mp_capacity - mp_begin)) // If n > capacity ...
    {
        this_type temp(n, value, m_allocator); // We have little choice but to reallocate with new memory.
        swap(temp);
    }
    else if (n > size_type(mp_end - mp_begin)) // If n > size ...
    {
        eastl::fill(mp_begin, mp_end, value);
        eastl::uninitialized_fill_n_ptr(mp_end, n - size_type(mp_end - mp_begin), value);
        mp_end += n - size_type(mp_end - mp_begin);
    }
    else // else 0 <= n <= size
    {
        eastl::fill_n(mp_begin, n, value);
        erase(mp_begin + n, mp_end);
    }
}

template <typename T, typename allocator>
template <typename input_iterator, bool bMove>
void vector<T, allocator>::do_assign_from_iterator(input_iterator first, input_iterator last, EASTL_ITC_NS::input_iterator_tag)
{
    iterator position(mp_begin);

    while ((position != mp_end) && (first != last))
    {
        *position = *first;
        ++first;
        ++position;
    }
    if (first == last)
        erase(position, mp_end);
    else
        insert(mp_end, first, last);
}

template <typename T, typename allocator>
template <typename RandomAccessIterator, bool bMove>
void vector<T, allocator>::do_assign_from_iterator(RandomAccessIterator first, RandomAccessIterator last, EASTL_ITC_NS::random_access_iterator_tag)
{
    const size_type n = (size_type)eastl::distance(first, last);

    if (n > size_type(mp_capacity - mp_begin)) // If n > capacity ...
    {
        pointer const pNewData = DoRealloc(n, first, last, bMove ? should_move_tag() : should_copy_tag());
        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = mp_begin + n;
        mp_capacity = mp_end;
    }
    else if (n <= size_type(mp_end - mp_begin)) // If n <= size ...
    {
        pointer const pNewEnd = eastl::copy(first, last, mp_begin); // Since we are copying to mp_begin, we don't have to worry about needing copy_backward or a memmove-like copy (as opposed to memcpy-like copy).
        eastl::destruct(pNewEnd, mp_end);
        mp_end = pNewEnd;
    }
    else // else size < n <= capacity
    {
        RandomAccessIterator position = first + (mp_end - mp_begin);
        eastl::copy(first, position, mp_begin); // Since we are copying to mp_begin, we don't have to worry about needing copy_backward or a memmove-like copy (as opposed to memcpy-like copy).
        mp_end = eastl::uninitialized_copy_ptr(position, last, mp_end);
    }
}

template <typename T, typename allocator>
template <typename Integer>
inline void vector<T, allocator>::DoInsert(const_iterator position, Integer n, Integer value, true_type)
{
    DoInsertValues(position, static_cast<size_type>(n), static_cast<value_type>(value));
}

template <typename T, typename allocator>
template <typename input_iterator>
inline void vector<T, allocator>::DoInsert(const_iterator position, input_iterator first, input_iterator last, false_type)
{
    typedef typename eastl::iterator_traits<input_iterator>::iterator_category IC;
    DoInsertFromIterator(position, first, last, IC());
}

template <typename T, typename allocator>
template <typename input_iterator>
inline void vector<T, allocator>::DoInsertFromIterator(const_iterator position, input_iterator first, input_iterator last, EASTL_ITC_NS::input_iterator_tag)
{
    for (; first != last; ++first, ++position)
        position = insert(position, *first);
}

template <typename T, typename allocator>
template <typename BidirectionalIterator>
void vector<T, allocator>::DoInsertFromIterator(const_iterator position, BidirectionalIterator first, BidirectionalIterator last, EASTL_ITC_NS::bidirectional_iterator_tag)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position > mp_end)))
        EASTL_FAIL_MSG("vector::insert -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);

    if (first != last)
    {
        const size_type n = (size_type)eastl::distance(first, last);  // n is the number of elements we are inserting.

        if (n <= size_type(mp_capacity - mp_end)) // If n fits within the existing capacity...
        {
            const size_type nExtra = static_cast<size_type>(mp_end - destPosition);

            if (n < nExtra) // If the inserted values are entirely within initialized memory (i.e. are before mp_end)...
            {
                eastl::uninitialized_copy_ptr(mp_end - n, mp_end, mp_end);
                eastl::copy_backward(destPosition, mp_end - n, mp_end); // We need copy_backward because of potential overlap issues.
                eastl::copy(first, last, destPosition);
            }
            else
            {
                BidirectionalIterator iTemp = first;
                eastl::advance(iTemp, nExtra);
                eastl::uninitialized_copy_ptr(iTemp, last, mp_end);
                eastl::uninitialized_copy_ptr(destPosition, mp_end, mp_end + n - nExtra);
                eastl::copy_backward(first, iTemp, destPosition + nExtra);
            }

            mp_end += n;
        }
        else // else we need to expand our capacity.
        {
            const size_type nPrevSize = size_type(mp_end - mp_begin);
            const size_type nGrowSize = get_new_capacity(nPrevSize);
            const size_type nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
            pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
            pointer pNewEnd = pNewData;
            try
            {
                pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);
                pNewEnd = eastl::uninitialized_copy_ptr(first, last, pNewEnd);
                pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, pNewEnd);
            }
            catch (...)
            {
                eastl::destruct(pNewData, pNewEnd);
                do_free(pNewData, nNewSize);
                throw;
            }
#else
            pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);
            pNewEnd = eastl::uninitialized_copy_ptr(first, last, pNewEnd);
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, pNewEnd);
#endif

            eastl::destruct(mp_begin, mp_end);
            do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

            mp_begin = pNewData;
            mp_end = pNewEnd;
            mp_capacity = pNewData + nNewSize;
        }
    }
}

template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValues(const_iterator position, size_type n, const value_type& value)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position > mp_end)))
        EASTL_FAIL_MSG("vector::insert -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);

    if (n <= size_type(mp_capacity - mp_end)) // If n is <= capacity...
    {
        if (n > 0) // To do: See if there is a way we can eliminate this 'if' statement.
        {
            // To consider: Make this algorithm work more like DoInsertValue whereby a pointer to value is used.
            const value_type temp = value;
            const size_type nExtra = static_cast<size_type>(mp_end - destPosition);

            if (n < nExtra)
            {
                eastl::uninitialized_copy_ptr(mp_end - n, mp_end, mp_end);
                eastl::copy_backward(destPosition, mp_end - n, mp_end); // We need copy_backward because of potential overlap issues.
                eastl::fill(destPosition, destPosition + n, temp);
            }
            else
            {
                eastl::uninitialized_fill_n_ptr(mp_end, n - nExtra, temp);
                eastl::uninitialized_copy_ptr(destPosition, mp_end, mp_end + n - nExtra);
                eastl::fill(destPosition, mp_end, temp);
            }

            mp_end += n;
        }
    }
    else // else n > capacity
    {
        const size_type nPrevSize = size_type(mp_end - mp_begin);
        const size_type nGrowSize = get_new_capacity(nPrevSize);
        const size_type nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        pointer const pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
        pointer pNewEnd = pNewData;
        try
        {
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);
            eastl::uninitialized_fill_n_ptr(pNewEnd, n, value);
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, pNewEnd + n);
        }
        catch (...)
        {
            eastl::destruct(pNewData, pNewEnd);
            do_free(pNewData, nNewSize);
            throw;
        }
#else
        pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);
        eastl::uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, pNewEnd + n);
#endif

        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = pNewEnd;
        mp_capacity = pNewData + nNewSize;
    }
}

template <typename T, typename allocator>
void vector<T, allocator>::do_clear_capacity() // This function exists because set_capacity() currently indirectly requires value_type to be default-constructible, 
{                                            // and some functions that need to clear our capacity (e.g. operator=) aren't supposed to require default-constructibility. 
    clear();
    this_type temp(*this);  // This is the simplest way to accomplish this, 
    swap(temp);             // and it is as efficient as any other.
}

template <typename T, typename allocator>
void vector<T, allocator>::DoGrow(size_type n)
{
    pointer const pNewData = do_allocate(n);

    pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);

    eastl::destruct(mp_begin, mp_end);
    do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

    mp_begin = pNewData;
    mp_end = pNewEnd;
    mp_capacity = pNewData + n;
}

template <typename T, typename allocator>
inline void vector<T, allocator>::DoSwap(this_type& x)
{
    eastl::swap(mp_begin, x.mp_begin);
    eastl::swap(mp_end, x.mp_end);
    eastl::swap(mp_capacity, x.mp_capacity);
    eastl::swap(m_allocator, x.m_allocator);  // We do this even if EASTL_ALLOCATOR_COPY_ENABLED is 0.
}

// The code duplication between this and the version that takes no value argument and default constructs the values
// is unfortunate but not easily resolved without relying on C++11 perfect forwarding.
template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValuesEnd(size_type n, const value_type& value)
{
    if (n > size_type(mp_capacity - mp_end))
    {
        const size_type nPrevSize = size_type(mp_end - mp_begin);
        const size_type nGrowSize = get_new_capacity(nPrevSize);
        const size_type nNewSize = eastl::max(nGrowSize, nPrevSize + n);
        pointer const pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
        pointer pNewEnd = pNewData; // Assign pNewEnd a value here in case the copy throws.
        try
        {
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
        }
        catch (...)
        {
            eastl::destruct(pNewData, pNewEnd);
            do_free(pNewData, nNewSize);
            throw;
        }
#else
        pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
#endif

        eastl::uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd += n;

        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = pNewEnd;
        mp_capacity = pNewData + nNewSize;
    }
    else
    {
        eastl::uninitialized_fill_n_ptr(mp_end, n, value);
        mp_end += n;
    }
}

template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValuesEnd(size_type n)
{
    if (n > size_type(mp_capacity - mp_end))
    {
        const size_type nPrevSize = size_type(mp_end - mp_begin);
        const size_type nGrowSize = get_new_capacity(nPrevSize);
        const size_type nNewSize = eastl::max(nGrowSize, nPrevSize + n);
        pointer const pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
        pointer pNewEnd = pNewData;  // Assign pNewEnd a value here in case the copy throws.
        try { pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData); }
        catch (...)
        {
            eastl::destruct(pNewData, pNewEnd);
            do_free(pNewData, nNewSize);
            throw;
        }
#else
        pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
#endif

        eastl::uninitialized_default_fill_n(pNewEnd, n);
        pNewEnd += n;

        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = pNewEnd;
        mp_capacity = pNewData + nNewSize;
    }
    else
    {
        eastl::uninitialized_default_fill_n(mp_end, n);
        mp_end += n;
    }
}

#if EASTL_MOVE_SEMANTICS_ENABLED && EASTL_VARIADIC_TEMPLATES_ENABLED // If we can do variadic arguments...
template <typename T, typename allocator>
template<typename... Args>
void vector<T, allocator>::DoInsertValue(const_iterator position, Args&&... args)
{
    // To consider: It's feasible that the args is from a value_type comes from within the current sequence itself and 
    // so we need to be sure to handle that case. This is different from insert(position, const value_type&) because in 
    // this case value is potentially being modified.

#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position > mp_end)))
        EASTL_FAIL_MSG("vector::insert/emplace -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);

    if (mp_end != mp_capacity) // If size < capacity ...
    {
        // We need to take into account the possibility that args is a value_type that comes from within the vector itself.
        // creating a temporary value on the stack here is not an optimal way to solve this because sizeof(value_type) may be
        // too much for the given platform. An alternative solution may be to specialize this function for the case of the
        // argument being const value_type& or value_type&&.
        EASTL_ASSERT(position < mp_end);                                 // While insert at end() is valid, our design is such that calling code should handle that case before getting here, as our streamlined logic directly doesn't handle this particular case due to resulting negative ranges.
#if EASTL_USE_FORWARD_WORKAROUND
        auto value = value_type(eastl::forward<Args>(args)...);     // Workaround for compiler bug in VS2013 which results in a compiler internal crash while compiling this code.
#else
        value_type  value(eastl::forward<Args>(args)...);           // Need to do this before the move_backward below because maybe args refers to something within the moving range.
#endif
        ::new(static_cast<void*>(mp_end)) value_type(eastl::move(*(mp_end - 1)));      // mp_end is uninitialized memory, so we must construct into it instead of move into it like we do with the other elements below.
        eastl::move_backward(destPosition, mp_end - 1, mp_end);           // We need to go backward because of potential overlap issues.
        eastl::destruct(destPosition);
        ::new(static_cast<void*>(destPosition)) value_type(eastl::move(value));                             // Move the value argument to the given position.
        ++mp_end;
    }
    else // else (size == capacity)
    {
        const size_type nPosSize = size_type(destPosition - mp_begin); // Index of the insertion position.
        const size_type nPrevSize = size_type(mp_end - mp_begin);
        const size_type nNewSize = get_new_capacity(nPrevSize);
        pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
        pointer pNewEnd = pNewData;
        try
        {   // To do: We are not handling exceptions properly below.  In particular we don't want to 
            // call eastl::destruct on the entire range if only the first part of the range was costructed.
            ::new((void*)(pNewData + nPosSize)) value_type(eastl::forward<Args>(args)...);              // Because the old data is potentially being moved rather than copied, we need to move.
            pNewEnd = NULL;                                                                             // Set to NULL so that in catch we can tell the exception occurred during the next call.
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);       // the value first, because it might possibly be a reference to the old data being moved.
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, ++pNewEnd);
        }
        catch (...)
        {
            if (pNewEnd)
                eastl::destruct(pNewData, pNewEnd);                                         // Destroy what has been constructed so far.
            else
                eastl::destruct(pNewData + nPosSize);                                       // The exception occurred during the first unintialized move, so destroy only the value at nPosSize.
            do_free(pNewData, nNewSize);
            throw;
        }
#else
        ::new((void*)(pNewData + nPosSize)) value_type(eastl::forward<Args>(args)...);                  // Because the old data is potentially being moved rather than copied, we need to move 
        pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);   // the value first, because it might possibly be a reference to the old data being moved.
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, ++pNewEnd);            // Question: with exceptions disabled, do we asssume all operations are noexcept and thus there's no need for uninitialized_move_ptr_if_noexcept?
#endif

        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = pNewEnd;
        mp_capacity = pNewData + nNewSize;
    }
}
#else
////////////////////////////////////////////////////////////////////////////////////////////////////
// Note: The following two sets of two functions are nearly copies of the above two functions.
// We (nearly) duplicate code here instead of trying to fold the all nine of these functions into 
// three more generic functions because: 1) you can't really make just three functions but rather 
// would need to break them apart somewhat, and 2) these duplications are eventually going away 
// because they aren't needed with C++11 compilers, though that may not be until the year 2020.
////////////////////////////////////////////////////////////////////////////////////////////////////

#if EASTL_MOVE_SEMANTICS_ENABLED
// To consider: Is there any practical means to merge the following DoInsertValue functions? 
// They are 90% the same as each other with the only difference being the use of eastl::move(value) usage.
// However, it isn't simple to fold that difference because value_type& and value_type&& are treated 
// significantly differently and constructing objects with them executes different code.

template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValue(const_iterator position, value_type&& value)
{
    // To consider: It's feasible that value comes from within the current sequence itself and so we need to be 
    // sure to handle that case. This is different from insert(position, const value_type&) because in this case 
    // value is potentially being modified.

#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position > mp_end)))
        EASTL_FAIL_MSG("vector::insert/emplace -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);

    if (mp_end != mp_capacity) // If size < capacity (and we can do this without reallocation)...
    {
        // We need to take into account the possibility that value may come from within the vector itself.
        EASTL_ASSERT(position < mp_end);                                 // While insert at end() is valid, our design is such that calling code should handle that case before getting here, as our streamlined logic directly doesn't handle this particular case due to resulting negative ranges.
        const T* pValue = &value;
        if ((pValue >= destPosition) && (pValue < mp_end))                // If value comes from within the range to be moved...
            ++pValue;                                                   // Set pValue to be where it will be after the copy.
        ::new(static_cast<void*>(mp_end)) value_type(eastl::move(*(mp_end - 1)));      // mp_end is uninitialized memory, so we must construct into it instead of move into it like we do with the other elements below.
        eastl::move_backward(destPosition, mp_end - 1, mp_end);           // We need to go backward because of potential overlap issues.
        eastl::destruct(destPosition);
        ::new(static_cast<void*>(destPosition)) value_type(eastl::move(value));                             // Move the value argument to the given position.
        ++mp_end;
    }
    else // else (size == capacity)
    {
        const size_type nPosSize = size_type(destPosition - mp_begin); // Index of the insertion position.
        const size_type nPrevSize = size_type(mp_end - mp_begin);
        const size_type nNewSize = get_new_capacity(nPrevSize);
        pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
        pointer pNewEnd = pNewData;
        try
        {
            ::new((void*)(pNewData + nPosSize)) value_type(eastl::move(value));                         // Because the old data is being moved rather than copied, we need to move the value first, 
            pNewEnd = NULL;                                                                             // Set to NULL so that in catch we can tell the exception occurred during the next call.
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);       // because it might possibly be a reference to the old data being moved.
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, ++pNewEnd);
        }
        catch (...)
        {
            if (pNewEnd)
                eastl::destruct(pNewData, pNewEnd);                                         // Destroy what has been constructed so far.
            else
                eastl::destruct(pNewData + nPosSize);                                       // The exception occurred during the first unintialized move, so destroy only the value at nPosSize.
            do_free(pNewData, nNewSize);
            throw;
        }
#else
        ::new((void*)(pNewData + nPosSize)) value_type(eastl::move(value));                             // Because the old data is being moved rather than copied, we need to move the value first, 
        pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);   // because it might possibly be a reference to the old data being moved.
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, ++pNewEnd);
#endif

        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = pNewEnd;
        mp_capacity = pNewData + nNewSize;
    }
}
#endif

template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValue(const_iterator position, const value_type& value)
{
#if EASTL_ASSERT_ENABLED
    if (EASTL_UNLIKELY((position < mp_begin) || (position > mp_end)))
        EASTL_FAIL_MSG("vector::insert/emplace -- invalid position");
#endif

    // C++11 stipulates that position is const_iterator, but the return value is iterator.
    iterator destPosition = const_cast<value_type*>(position);

    if (mp_end != mp_capacity) // If size < capacity ...
    {
        // We need to take into account the possibility that value may come from within the vector itself.
        EASTL_ASSERT(position < mp_end);                                 // While insert at end() is valid, our design is such that calling code should handle that case before getting here, as our streamlined logic directly doesn't handle this particular case due to resulting negative ranges.
        const T* pValue = &value;
        if ((pValue >= destPosition) && (pValue < mp_end))        // If value comes from within the range to be moved...
            ++pValue;                                           // Set pValue to be where it will be after the copy.
        ::new((void*)mp_end) value_type(*(mp_end - 1));           // mp_end is uninitialized memory, so we must construct into it instead of move into it like we do with the other elements below.
        eastl::move_backward(destPosition, mp_end - 1, mp_end);   // We need to go backward because of potential overlap issues.
        *destPosition = *pValue;                                // Copy the value argument to the given position.
        ++mp_end;
    }
    else // else (size == capacity)
    {
        const size_type nPosSize = size_type(destPosition - mp_begin); // Index of the insertion position.
        const size_type nPrevSize = size_type(mp_end - mp_begin);
        const size_type nNewSize = get_new_capacity(nPrevSize);
        pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
        pointer pNewEnd = pNewData;
        try
        {
            ::new((void*)(pNewData + nPosSize)) value_type(value);                                      // Because the old data is being moved rather than copied, we need to move the value first, 
            pNewEnd = NULL;                                                                             // Set to NULL so that in catch we can tell the exception occurred during the next call.
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);       // because it might possibly be a reference to the old data being moved.
            pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, ++pNewEnd);
        }
        catch (...)
        {
            if (pNewEnd)
                eastl::destruct(pNewData, pNewEnd);                                         // Destroy what has been constructed so far.
            else
                eastl::destruct(pNewData + nPosSize);                                       // The exception occurred during the first unintialized move, so destroy only the value at nPosSize.
            do_free(pNewData, nNewSize);
            throw;
        }
#else
        ::new((void*)(pNewData + nPosSize)) value_type(value);                                          // Because the old data is being moved rather than copied, we need to move the value first, 
        pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, destPosition, pNewData);   // because it might possibly be a reference to the old data being moved.
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(destPosition, mp_end, ++pNewEnd);
#endif

        eastl::destruct(mp_begin, mp_end);
        do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

        mp_begin = pNewData;
        mp_end = pNewEnd;
        mp_capacity = pNewData + nNewSize;
    }
}

#endif

#if EASTL_MOVE_SEMANTICS_ENABLED && EASTL_VARIADIC_TEMPLATES_ENABLED
template <typename T, typename allocator>
template<typename... Args>
void vector<T, allocator>::DoInsertValueEnd(Args&&... args)
{
    const size_type nPrevSize = size_type(mp_end - mp_begin);
    const size_type nNewSize = get_new_capacity(nPrevSize);
    pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
    pointer pNewEnd = pNewData; // Assign pNewEnd a value here in case the copy throws.
    try
    {
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
        ::new((void*)pNewEnd) value_type(eastl::forward<Args>(args)...);
        pNewEnd++;
    }
    catch (...)
    {
        eastl::destruct(pNewData, pNewEnd);
        do_free(pNewData, nNewSize);
        throw;
    }
#else
    pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
    ::new((void*)pNewEnd) value_type(eastl::forward<Args>(args)...);
    pNewEnd++;
#endif

    eastl::destruct(mp_begin, mp_end);
    do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

    mp_begin = pNewData;
    mp_end = pNewEnd;
    mp_capacity = pNewData + nNewSize;
}
#else
#if EASTL_MOVE_SEMANTICS_ENABLED
template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValueEnd(value_type&& value)
{
    const size_type nPrevSize = size_type(mp_end - mp_begin);
    const size_type nNewSize = get_new_capacity(nPrevSize);
    pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
    pointer pNewEnd = pNewData; // Assign pNewEnd a value here in case the copy throws.
    try
    {
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
        ::new((void*)pNewEnd) value_type(eastl::move(value));
        pNewEnd++;
    }
    catch (...)
    {
        eastl::destruct(pNewData, pNewEnd);
        do_free(pNewData, nNewSize);
        throw;
    }
#else
    pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
    ::new((void*)pNewEnd) value_type(eastl::move(value));
    pNewEnd++;
#endif

    eastl::destruct(mp_begin, mp_end);
    do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

    mp_begin = pNewData;
    mp_end = pNewEnd;
    mp_capacity = pNewData + nNewSize;
}
#endif

template <typename T, typename allocator>
void vector<T, allocator>::DoInsertValueEnd(const value_type& value)
{
    const size_type nPrevSize = size_type(mp_end - mp_begin);
    const size_type nNewSize = get_new_capacity(nPrevSize);
    pointer const   pNewData = do_allocate(nNewSize);

#if EASTL_EXCEPTIONS_ENABLED
    pointer pNewEnd = pNewData; // Assign pNewEnd a value here in case the copy throws.
    try
    {
        pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
        ::new((void*)pNewEnd) value_type(value);
        pNewEnd++;
    }
    catch (...)
    {
        eastl::destruct(pNewData, pNewEnd);
        do_free(pNewData, nNewSize);
        throw;
    }
#else
    pointer pNewEnd = eastl::uninitialized_move_ptr_if_noexcept(mp_begin, mp_end, pNewData);
    ::new((void*)pNewEnd) value_type(value);
    pNewEnd++;
#endif

    eastl::destruct(mp_begin, mp_end);
    do_free(mp_begin, (size_type)(mp_capacity - mp_begin));

    mp_begin = pNewData;
    mp_end = pNewEnd;
    mp_capacity = pNewData + nNewSize;
}
#endif

template <typename T, typename allocator>
inline bool vector<T, allocator>::validate() const GEA_NOEXCEPT
{
    if (mp_end < mp_begin)
    return false;
    if (mp_capacity < mp_end)
        return false;
    return true;
}

    template <typename T, typename allocator>
inline int vector<T, allocator>::validate_iterator(const_iterator i) const GEA_NOEXCEPT
{
    if (i >= mp_begin)
    {
        if (i < mp_end)
            return (isf_valid | isf_current | isf_can_dereference);

        if (i <= mp_end)
            return (isf_valid | isf_current);
    }

    return isf_none;
}


    ///////////////////////////////////////////////////////////////////////
    // global operators
    ///////////////////////////////////////////////////////////////////////

    template <typename T, typename allocator>
inline bool operator==(const vector<T, allocator>& a, const vector<T, allocator>& b)
{
    return ((a.size() == b.size()) && equal(a.begin(), a.end(), b.begin()));
}

template <typename T, typename allocator>
inline bool operator!=(const vector<T, allocator>& a, const vector<T, allocator>& b)
{
    return ((a.size() != b.size()) || !equal(a.begin(), a.end(), b.begin()));
}

template <typename T, typename allocator>
inline bool operator<(const vector<T, allocator>& a, const vector<T, allocator>& b)
{
    return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T, typename allocator>
inline bool operator>(const vector<T, allocator>& a, const vector<T, allocator>& b)
{
    return b < a;
}

template <typename T, typename allocator>
inline bool operator<=(const vector<T, allocator>& a, const vector<T, allocator>& b)
{
    return !(b < a);
}

template <typename T, typename allocator>
inline bool operator>=(const vector<T, allocator>& a, const vector<T, allocator>& b)
{
    return !(a < b);
}

template <typename T, typename allocator>
inline void swap(vector<T, allocator>& a, vector<T, allocator>& b)
{
    a.swap(b);
}

} // namespace gea //
