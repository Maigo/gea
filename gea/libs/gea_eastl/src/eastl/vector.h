#ifndef __GEA_VECTOR_H__
#define __GEA_VECTOR_H__

namespace gea
{

// ------------------------------------------------------------------------- //
// vector_base                                                               //
// ------------------------------------------------------------------------- //

template <typename T, typename allocator>
struct vector_base
{
	typedef allocator    allocator_type;
	typedef gea_size_t   size_type;
	typedef ptrdiff_t    difference_type;

	static const size_type npos       = (size_type)-1;  /// 'npos' means non-valid position or simply non-position.
	static const size_type k_max_size = (size_type)-2;  /// -1 is reserved for 'npos'. It also happens to be slightly beneficial that k_max_size is a value less than -1, as it helps us deal with potential integer wraparound issues.

protected:
	T*              mp_begin;
	T*              mp_end;
	T*              mp_capacity;
	allocator_type  m_allocator;  // To do: Use base class optimization to make this go away.

public:
	vector_base(const allocator_type& allocator);
	vector_base(size_type n, const allocator_type& allocator);

	~vector_base();

	const allocator_type& get_allocator() const GEA_NOEXCEPT;
    allocator_type&       get_allocator() GEA_NOEXCEPT;
	void                  set_allocator(const allocator_type& allocator);

protected:
	T*        do_allocate(size_type n);
	void      do_free(T* p, size_type n);
	size_type get_new_capacity(size_type current_capacity);
};

// ------------------------------------------------------------------------- //
// vector                                                                    //
// ------------------------------------------------------------------------- //

template <typename T, typename allocator>
class vector : public VectorBase<T, Allocator>
{
	typedef VectorBase<T, Allocator>                      base_type;
	typedef vector<T, Allocator>                          this_type;

public:
	typedef T                                             value_type;
	typedef T*                                            pointer;
	typedef const T*                                      const_pointer;
	typedef T&                                            reference;
	typedef const T&                                      const_reference;  // Maintainer note: We want to leave iterator defined as T* -- at least in release builds -- as this gives some algorithms an advantage that optimizers cannot get around.
	typedef T*                                            iterator;         // Note: iterator is simply T* right now, but this will likely change in the future, at least for debug builds. 
	typedef const T*                                      const_iterator;   //       Do not write code that relies on iterator being T*. The reason it will 
	typedef eastl::reverse_iterator<iterator>             reverse_iterator; //       change in the future is that a debugging iterator system will be created.
	typedef eastl::reverse_iterator<const_iterator>       const_reverse_iterator;    
	typedef typename base_type::size_type                 size_type;
	typedef typename base_type::difference_type           difference_type;
	typedef typename base_type::allocator_type            allocator_type;

	using base_type::mp_begin;
	using base_type::mp_end;
	using base_type::mp_capacity;
	using base_type::m_allocator;
	using base_type::npos;
	using base_type::get_new_capacity;
	using base_type::do_allocate;
	using base_type::do_free;

public:
	explicit vector(const allocator_type& allocator);
	explicit vector(size_type n, const allocator_type& allocator);
	vector(size_type n, const value_type& value, const allocator_type& allocator);
	vector(const this_type& x);
	vector(const this_type& x, const allocator_type& allocator);
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		vector(this_type&& x);
//		vector(this_type&& x, const allocator_type& allocator);
//	#endif
//	vector(std::initializer_list<value_type> ilist, const allocator_type& allocator = EASTL_VECTOR_DEFAULT_ALLOCATOR);

	template <typename input_iterator>
	vector(input_iterator first, input_iterator last, const allocator_type& allocator = EASTL_VECTOR_DEFAULT_ALLOCATOR);

	~vector();

	this_type& operator=(const this_type& x);
//	this_type& operator=(std::initializer_list<value_type> ilist);
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		this_type& operator=(this_type&& x);
//	#endif

	void swap(this_type& x);

	void assign(size_type n, const value_type& value);

	template <typename input_iterator>
	void assign(input_iterator first, input_iterator last);

//	void assign(std::initializer_list<value_type> ilist);

	iterator       begin() GEA_NOEXCEPT;
	const_iterator begin() const GEA_NOEXCEPT;
	const_iterator cbegin() const GEA_NOEXCEPT;

	iterator       end() GEA_NOEXCEPT;
	const_iterator end() const GEA_NOEXCEPT;
	const_iterator cend() const GEA_NOEXCEPT;

	reverse_iterator       rbegin() GEA_NOEXCEPT;
	const_reverse_iterator rbegin() const GEA_NOEXCEPT;
	const_reverse_iterator crbegin() const GEA_NOEXCEPT;

	reverse_iterator       rend() GEA_NOEXCEPT;
	const_reverse_iterator rend() const GEA_NOEXCEPT;
	const_reverse_iterator crend() const GEA_NOEXCEPT;

	bool      empty() const GEA_NOEXCEPT;
	size_type size() const GEA_NOEXCEPT;
	size_type capacity() const GEA_NOEXCEPT;

	void resize(size_type n, const value_type& value);
	void resize(size_type n);
	void reserve(size_type n);
	void set_capacity(size_type n = base_type::npos);   // Revises the capacity to the user-specified value. Resizes the container to match the capacity if the requested capacity n is less than the current size. If n == npos then the capacity is reallocated (if necessary) such that capacity == size.
	void shrink_to_fit();                               // C++11 function which is the same as set_capacity().

	pointer       data() GEA_NOEXCEPT;
	const_pointer data() const GEA_NOEXCEPT;

	reference       operator[](size_type n);
	const_reference operator[](size_type n) const;

	reference       at(size_type n);
	const_reference at(size_type n) const;

	reference       front();
	const_reference front() const;

	reference       back();
	const_reference back() const;

	void      push_back(const value_type& value);
	reference push_back();
	void*     push_back_uninitialized();
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		void  push_back(value_type&& value);
//	#endif
	void      pop_back();

//	#if EASTL_MOVE_SEMANTICS_ENABLED && EASTL_VARIADIC_TEMPLATES_ENABLED
//		template<class... Args>
//		iterator emplace(const_iterator position, Args&&... args);
//
//		template<class... Args>
//		void emplace_back(Args&&... args);
//	#else
//		#if EASTL_MOVE_SEMANTICS_ENABLED
//			iterator emplace(const_iterator position, value_type&& value);
//			void emplace_back(value_type&& value);
//		#endif

		iterator emplace(const_iterator position, const value_type& value);
		void emplace_back(const value_type& value);
//	#endif

	iterator insert(const_iterator position, const value_type& value);
	void     insert(const_iterator position, size_type n, const value_type& value);
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		iterator insert(const_iterator position, value_type&& value);
//	#endif
//	iterator insert(const_iterator position, std::initializer_list<value_type> ilist);

	template <typename input_iterator>
	void insert(const_iterator position, input_iterator first, input_iterator last);

	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);
	iterator erase_unsorted(const_iterator position);         // Same as erase, except it doesn't preserve order, but is faster because it simply copies the last item in the vector over the erased position.

	reverse_iterator erase(const_reverse_iterator position);
	reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);
	reverse_iterator erase_unsorted(const_reverse_iterator position);

	void clear() GEA_NOEXCEPT;
	void reset_lose_memory() GEA_NOEXCEPT;                       // This is a unilateral reset to an initially empty state. No destructors are called, no deallocation occurs.

	bool validate() const GEA_NOEXCEPT;
	int  validate_iterator(const_iterator i) const GEA_NOEXCEPT;

//	#if EASTL_RESET_ENABLED
//		void reset() GEA_NOEXCEPT; // This function name is deprecated; use reset_lose_memory instead.
//	#endif

protected:
	// These functions do the real work of maintaining the vector. You will notice
	// that many of them have the same name but are specialized on iterator_tag
	// (iterator categories). This is because in these cases there is an optimized
	// implementation that can be had for some cases relative to others. Functions
	// which aren't referenced are neither compiled nor linked into the application.
	struct should_copy_tag{}; struct should_move_tag : public should_copy_tag{};

	template <typename ForwardIterator> // Allocates a pointer of array count n and copy-constructs it with [first,last).
	pointer do_realloc(size_type n, ForwardIterator first, ForwardIterator last, should_copy_tag);

	template <typename ForwardIterator> // Allocates a pointer of array count n and copy-constructs it with [first,last).
	pointer do_realloc(size_type n, ForwardIterator first, ForwardIterator last, should_move_tag);

	template <typename Integer>
	void do_init(Integer n, Integer value, true_type);

	template <typename input_iterator>
	void do_init(input_iterator first, input_iterator last, false_type);

	template <typename input_iterator>
	void do_init_from_iterator(input_iterator first, input_iterator last, EASTL_ITC_NS::input_iterator_tag);

	template <typename ForwardIterator>
    void do_init_from_iterator(ForwardIterator first, ForwardIterator last, EASTL_ITC_NS::forward_iterator_tag);

	template <typename Integer, bool bMove>
	void do_assign(Integer n, Integer value, true_type);

	template <typename input_iterator, bool bMove>
    void do_assign(input_iterator first, input_iterator last, false_type);

    void do_assign_values(size_type n, const value_type& value);

	template <typename input_iterator, bool bMove>
    void do_assign_from_iterator(input_iterator first, input_iterator last, EASTL_ITC_NS::input_iterator_tag);

	template <typename RandomAccessIterator, bool bMove>
    void do_assign_from_iterator(RandomAccessIterator first, RandomAccessIterator last, EASTL_ITC_NS::random_access_iterator_tag);

	template <typename Integer>
	void do_insert(const_iterator position, Integer n, Integer value, true_type);

	template <typename input_iterator>
    void do_insert(const_iterator position, input_iterator first, input_iterator last, false_type);

	template <typename input_iterator>
    void do_insert_from_iterator(const_iterator position, input_iterator first, input_iterator last, EASTL_ITC_NS::input_iterator_tag);

	template <typename BidirectionalIterator>
    void do_insert_from_iterator(const_iterator position, BidirectionalIterator first, BidirectionalIterator last, EASTL_ITC_NS::bidirectional_iterator_tag);

	void do_insert_values(const_iterator position, size_type n, const value_type& value);

	void do_insert_values_end(size_type n); // Default constructs n values
	void do_insert_values_end(size_type n, const value_type& value);

//	#if EASTL_MOVE_SEMANTICS_ENABLED && EASTL_VARIADIC_TEMPLATES_ENABLED // If we can do variadic arguments...
//		template<typename... Args>
//		void DoInsertValue(const_iterator position, Args&&... args);
//	#else
//		#if EASTL_MOVE_SEMANTICS_ENABLED
//			void DoInsertValue(const_iterator position, value_type&& value);
//		#endif
        void do_insert_value(const_iterator position, const value_type& value);
//	#endif

//	#if EASTL_MOVE_SEMANTICS_ENABLED && EASTL_VARIADIC_TEMPLATES_ENABLED
//		template<typename... Args>
//		void DoInsertValueEnd(Args&&... args);
//	#else
//		#if EASTL_MOVE_SEMANTICS_ENABLED
//			void DoInsertValueEnd(value_type&& value);
//		#endif
            void do_insert_value_end(const value_type& value);
//	#endif

	void do_clear_capacity();

	void do_grow(size_type n);

	void do_swap(this_type& x);
};

} // namespace gea //

#endif // __GEA_VECTOR_H__ //
