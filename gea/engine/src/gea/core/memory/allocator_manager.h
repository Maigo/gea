#ifndef __GEA_ALLOCATOR_MANAGER_H__
#define __GEA_ALLOCATOR_MANAGER_H__

// gea includes
#include <core/pattern/singleton.h>
#include <core/memory/allocator.h>

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

    allocator *mp_static_heap;
    allocator *mp_page_allocator;
    allocator *mp_heap_allocator;
};

} // namespace gea //

#include "allocator_manager.inl"

#endif // __GEA_ALLOCATOR_MANAGER_H__ //
