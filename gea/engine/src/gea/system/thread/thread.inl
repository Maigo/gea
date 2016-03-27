
#include <gea/utility/assert.h>

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// thread                                                                    //
// ------------------------------------------------------------------------- //
// constructors
inline thread::thread()
    : state_base(RUNNING), m_tid(0), m_thread_mask(), m_runnable(NULL)
{
    inherit_process_mask();
    internal::thread_set_current(m_thread);
    m_tid = internal::thread_get_tid(m_thread);
}
inline thread::thread(runnable *runnable)
    : state_base(EMPTY), m_tid(0), m_thread_mask(), m_runnable(runnable)
{
    inherit_process_mask();
}
inline thread::thread(runnable *runnable, const affinity_mask &thread_mask)
    : state_base(EMPTY), m_tid(0), m_thread_mask(thread_mask), m_runnable(runnable) {}
// current thread
inline thread thread::get_current_thread() {
    return thread();
}
// create
inline thread thread::fork(runnable *r) {
    return thread(r, m_thread_mask);
}

inline bool thread::construct() {
    if ( !is_state(EMPTY) ) return false;
    return internal::thread_create(m_thread, (internal::thread_cb) thread::entry_point, static_cast<void*>(this), &m_tid) &&
           internal::thread_bind_context(m_thread, m_thread_mask);
}
inline bool thread::start() {
    if ( !is_state(PAUSED) ) return false;
    return internal::thread_resume(m_thread);
}
inline bool thread::suspend() {
    if ( !is_state(RUNNING) ) return false;
    return internal::thread_suspend(m_thread);
}
inline bool thread::wait(uint32_t ms) const {
    if ( !is_state(RUNNING) ) return false;
    return internal::thread_wait(m_thread, ms);
}
inline bool thread::kill() {
    if ( !is_state(RUNNING) ) return false;
    return internal::thread_kill(m_thread);
}

// thread affinity mask (tam)
inline void thread::set_thread_mask(const affinity_mask& thread_mask) {
    if (is_state(EMPTY) || internal::thread_bind_context(m_thread, thread_mask))
        m_thread_mask = thread_mask;
}
inline const affinity_mask& thread::get_thread_mask() const { return m_thread_mask; }
inline void thread::inherit_process_mask() {
    affinity_mask process_mask;
    if (internal::get_process_affinity_mask(&process_mask, NULL) == GEA_OK)
        m_thread_mask = process_mask;
}

inline uint32_t thread::main() {
    set_state(RUNNING);
    uint32_t ret = m_runnable->main();
    set_state(PAUSED);
    return ret;
}


} // namespace prl //
} // namespace gea //
