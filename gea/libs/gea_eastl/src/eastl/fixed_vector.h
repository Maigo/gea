#ifndef __GEA_FIXED_VECTOR_H__
#define __GEA_FIXED_VECTOR_H__

#include <eastl/vector.h>

namespace gea {

// ------------------------------------------------------------------------- //
// fixed_vector                                                              //
// ------------------------------------------------------------------------- //
template <typename T, size_t N>
class fixed_vector : public vector<T, fixed_vector_allocator<sizeof(T), N, GEA_ALIGN_OF(T), 0> >
{
public:
	typedef fixed_vector_allocator<sizeof(T), N, GEA_ALIGN_OF(T), 0>    fixed_allocator_type;
	typedef vector<T, fixed_allocator_type>                             base_type;
	typedef fixed_vector<T, N>                                          this_type;
	typedef typename base_type::size_type                               size_type;
	typedef typename base_type::value_type                              value_type;
	typedef typename base_type::reference                               reference;
	typedef typename base_type::iterator                                iterator;
	typedef typename base_type::const_iterator                          const_iterator;
	typedef aligned_buffer<N * sizeof(T), GEA_ALIGN_OF(T)>              aligned_buffer_type;

	enum { k_max_size = N };

	using base_type::mAllocator;
	using base_type::mpBegin;
	using base_type::mpEnd;
	using base_type::mpCapacity;
	using base_type::resize;
	using base_type::clear;
	using base_type::size;
	using base_type::assign;
	using base_type::npos;
	using base_type::DoAllocate;
	using base_type::DoFree;
	using base_type::DoAssign;
	using base_type::DoAssignFromIterator;

protected:
	aligned_buffer_type m_buffer;

public:
	fixed_vector();
	explicit fixed_vector(size_type n);
	fixed_vector(size_type n, const value_type& value);
	fixed_vector(const this_type& x);
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		fixed_vector(this_type&& x);
//		fixed_vector(this_type&& x, const overflow_allocator_type& overflowAllocator);
//	#endif
//	fixed_vector(std::initializer_list<T> ilist, const overflow_allocator_type& overflowAllocator = EASTL_FIXED_VECTOR_DEFAULT_ALLOCATOR);

	template <typename input_iterator>
    fixed_vector(input_iterator first, input_iterator last);

	this_type& operator=(const this_type& x);
//	this_type& operator=(std::initializer_list<T> ilist);
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		this_type& operator=(this_type&& x);
//	#endif

	void swap(this_type& x);

	void      set_capacity(size_type n);
	void      clear(bool free_overflow);
	void      reset_lose_memory();
	size_type max_size() const;
	bool      full() const;

	void*     push_back_uninitialized();
	void      push_back(const value_type& value);
	reference push_back();
//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		void  push_back(value_type&& value);
//	#endif

protected:
	void*     do_push_back_uninitialized();

	void      do_push_back(const value_type& value);

//	#if EASTL_MOVE_SEMANTICS_ENABLED
//		void      DoPushBackMove(value_type&& value);
//	#endif

	reference do_push_back();
};

} // namespace eastl

#include "fixed_vector.inl"

#endif // __GEA_FIXED_VECTOR_H__ //
