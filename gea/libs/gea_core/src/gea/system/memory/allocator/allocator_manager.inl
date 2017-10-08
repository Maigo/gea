#pragma once
#include "allocator_manager.h"

// gea includes
#include <gea/system/memory/allocator/allocator_heap.h>
#include <gea/system/memory/allocator/allocator_page.h>

//DEBUG
#include <new>

namespace gea {

// ------------------------------------------------------------------------- //
// allocator_manager                                                         //
// ------------------------------------------------------------------------- //
inline void allocator_manager::init() {
    // use static buffer to allocate static heap
    m_static_heap = ::new (m_buffer) heap_allocator(nullptr, m_buffer + sizeof(heap_allocator), BUFFER_SIZE - sizeof(heap_allocator));
    // which in turn is used to allocate page and heap allocators
    m_page_allocator = m_static_heap->make_new<page_allocator>("page_allocator");
    m_heap_allocator = m_static_heap->make_new<heap_allocator>("heap_allocator");
}
inline void allocator_manager::shutdown() {
    // deallocate heap and page allocators
    m_static_heap->make_delete(m_heap_allocator);
    m_heap_allocator = nullptr;
    
    m_static_heap->make_delete(m_page_allocator);
    m_page_allocator = nullptr;

    // call destructor
    m_static_heap->~allocator();
    m_static_heap = nullptr;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
