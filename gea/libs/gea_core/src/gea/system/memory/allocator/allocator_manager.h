#pragma once

// gea includes
#include <gea/core/pattern/singleton.h>
#include <gea/system/memory/allocator/allocator.h>

namespace gea {

// ------------------------------------------------------------------------- //
// allocator_manager                                                         //
// ------------------------------------------------------------------------- //
class allocator_manager : public singleton<allocator_manager> {
public:
    static const uint32_t BUFFER_SIZE = 128;

    inline void init();
    inline void shutdown();

private:
    uint8_t    m_buffer[BUFFER_SIZE];

    allocator *m_static_heap;
    allocator *m_page_allocator;
    allocator *m_heap_allocator;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "allocator_manager.inl"
