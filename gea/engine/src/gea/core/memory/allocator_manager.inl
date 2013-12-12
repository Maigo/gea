
// gea includes
#include <core/memory/allocator_heap.h>
#include <core/memory/allocator_page.h>

//DEBUG
#include <new>

namespace gea {

// ------------------------------------------------------------------------- //
// allocator_manager                                                         //
// ------------------------------------------------------------------------- //
inline void allocator_manager::init() {
    // use static buffer to allocate static heap
    mp_static_heap = ::new (m_buffer) heap_allocator(NULL, m_buffer + sizeof(heap_allocator), BUFFER_SIZE - sizeof(heap_allocator));
    // which in turn is used to allocate page and heap allocators
    mp_page_allocator = mp_static_heap->make_new<page_allocator>("page_allocator");
    mp_heap_allocator = mp_static_heap->make_new<heap_allocator>("heap_allocator");
}
inline void allocator_manager::shutdown() {
    // deallocate heap and page allocators
    mp_static_heap->make_delete(mp_heap_allocator);
    mp_heap_allocator = NULL;
    
    mp_static_heap->make_delete(mp_page_allocator);
    mp_page_allocator = NULL;

    // call destructor
    mp_static_heap->~allocator();
    mp_static_heap = NULL;
}

} // namespace gea //
