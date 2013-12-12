#ifndef __GEA_PARALLEL_WIN32_H__
#define __GEA_PARALLEL_WIN32_H__

//TODO: remove!
#include <windows.h>

// gea engine includes
#include <gea/core/error/error_codes.h>

#include "parallel_base.h"

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// affinity_mask                                                             //
// ------------------------------------------------------------------------- //
class affinity_mask : public base_affinity_mask {
public:
    inline affinity_mask();
    inline affinity_mask(DWORD affinity_mask);

    // windows api finctions
    inline void set_affinity_mask(DWORD affinity_mask);
    inline DWORD get_affinity_mask() const;
};
// affinity mask cutter
typedef base_affinity_mask_cutter<affinity_mask> affinity_mask_cutter;

namespace internal {

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
err_code_t get_process_affinity_mask(affinity_mask* process_affinity_mask, affinity_mask* system_affinity_mask);    

// ------------------------------------------------------------------------- //
// mutex                                                                     //
// ------------------------------------------------------------------------- //
// wrapper structure
struct critical_section {
    CRITICAL_SECTION m_cs;
};
// internal functions
inline void cs_create_with_spincount(critical_section &cs, uint32_t spin_count);
inline void cs_destroy(critical_section &cs);

inline void cs_lock(critical_section &cs);
inline bool cs_try_lock(critical_section &cs);
inline bool cs_unlock(critical_section &cs);

inline void cs_set_spincount(critical_section &cs, const uint32_t &spin_count);

// ------------------------------------------------------------------------- //
// semaphore                                                                 //
// ------------------------------------------------------------------------- //
// wrapper structure
struct semaphore {
    HANDLE  m_handle;
};
// internal functions
inline void semaphore_create(semaphore &s, int32_t init, int32_t max_count);
inline void semaphore_destroy(semaphore &s);

inline bool semaphore_wait(semaphore &s, uint32_t ms);
inline bool semaphore_release(semaphore &s);
inline int32_t semaphore_value(const semaphore &s);

// ------------------------------------------------------------------------- //
// thread                                                                    //
// ------------------------------------------------------------------------- //
// wrapper structure
struct thread {
    HANDLE m_handle;
};
typedef uint32_t (*thread_cb)(void *); 

// internal functions
inline bool thread_create(thread &t, thread_cb *cb, void *param, uint32_t *tid = NULL);
inline bool thread_suspend(thread &t);
inline bool thread_resume(thread &t);

inline bool thread_wait(const thread &t, uint32_t ms);
inline bool thread_kill(thread &t);

inline bool thread_set_affinity_mask(thread &t, const affinity_mask &affinity_mask);

inline void thread_set_current(thread &t);
inline uint32_t thread_get_tid(const thread &t);

err_code_t thread_bind_context(thread &t, const affinity_mask& affinity_mask);

} // namespace internal //

} // namespace prl //
} // namespace gea //

#include "parallel_win32.inl"

#endif // __GEA_PARALLEL_WIN32_H__ //
