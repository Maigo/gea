
//DEBUG
#include <gea/utility/assert.h>

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// affinity_mask                                                             //
// ------------------------------------------------------------------------- //
inline affinity_mask::affinity_mask() : base_affinity_mask() {}
inline affinity_mask::affinity_mask(DWORD affinity_mask) : base_affinity_mask() {
    set_raw_affinity_mask(static_cast<uint32_t>(affinity_mask));
}

// windows api finctions
inline void affinity_mask::set_affinity_mask(DWORD affinity_mask) {
    set_raw_affinity_mask(static_cast<uint32_t>(affinity_mask));
}
inline DWORD affinity_mask::get_affinity_mask() const {
    return static_cast<DWORD>(get_raw_affinity_mask());
}

namespace internal {

// ------------------------------------------------------------------------- //
// mutex                                                                     //
// ------------------------------------------------------------------------- //
inline void cs_create_with_spincount(critical_section &cs, uint32_t spin_count) {
    InitializeCriticalSectionAndSpinCount( &cs.m_cs, static_cast<DWORD>(spin_count) );
}
inline void cs_destroy(critical_section &cs) {
    DeleteCriticalSection( &cs.m_cs );
}

inline void cs_lock(critical_section &cs) {
    EnterCriticalSection( &cs.m_cs );
}
inline bool cs_try_lock(critical_section &cs) {
    return (TryEnterCriticalSection( &cs.m_cs ) != 0);
}
inline bool cs_unlock(critical_section &cs) {
    LeaveCriticalSection( &cs.m_cs );
}

inline void cs_set_spincount(critical_section &cs, const uint32_t &spin_count) {
    SetCriticalSectionSpinCount( &cs.m_cs, static_cast<DWORD>(spin_count) );
}

// ------------------------------------------------------------------------- //
// semaphore                                                                 //
// ------------------------------------------------------------------------- //
inline void semaphore_create(semaphore &s, int32_t init, int32_t max_count) {
     s.m_handle = CreateSemaphore( NULL, init, max_count, NULL );
}
inline void semaphore_destroy(semaphore &s) {
    CloseHandle( s.m_handle );
}

inline bool semaphore_wait(semaphore &s, uint32_t ms) {
    return WaitForSingleObject( s.m_handle, ms ) == WAIT_OBJECT_0;
}
inline bool semaphore_release(semaphore &s) {
    return ReleaseSemaphore( s.m_handle, 1, 0 ) != 0;
}
inline int32_t semaphore_value(const semaphore &s) {
    long value = -1;
    ReleaseSemaphore( s.m_handle, 0, &value );
    return value;
}

// ------------------------------------------------------------------------- //
// thread                                                                    //
// ------------------------------------------------------------------------- //
inline bool thread_create(thread &t, thread_cb cb, void *param, uint32_t *tid) {
    t.m_handle = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) cb, param, CREATE_SUSPENDED, (DWORD *) tid);
    return t.m_handle != NULL;
}

inline bool thread_resume(thread &t) {
    return ResumeThread( t.m_handle ) != (DWORD) -1;
}
inline bool thread_suspend(thread &t) {
    return SuspendThread( t.m_handle ) != (DWORD) -1;
}

inline bool thread_wait(const thread &t, uint32_t ms) {
    return WaitForSingleObject( t.m_handle, ms ) == WAIT_OBJECT_0;
}
inline bool thread_kill(thread &t) {
    bool success = ( TerminateThread( t.m_handle, 1 ) != 0 ) && CloseHandle( t.m_handle );
    t.m_handle = 0x00;
    return success;
}

inline bool thread_set_affinity_mask(thread &t, const affinity_mask &affinity_mask) {
    return ( SetThreadAffinityMask(t.m_handle, affinity_mask.get_affinity_mask()) != 0 );
}

inline void thread_set_current(thread &t) {
    t.m_handle = GetCurrentThread();
}

inline uint32_t thread_get_tid(const thread &t) {
    return static_cast<uint32_t>( GetThreadId(t.m_handle) );
}

} // namespace internal //

} // namespace prl //
} // namespace gea //
