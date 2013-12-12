
#include <gea/engine/utility/assert.h>

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// mutex                                                                     //
// ------------------------------------------------------------------------- //
// constructors
inline mutex::mutex() : m_spin_count(DEFAULT_SPIN_COUNT), m_locked(false) {
    internal::cs_create_with_spincount( m_mutex, m_spin_count );
}
inline mutex::mutex(uint32_t spin_count) : m_spin_count(spin_count), m_locked(false) {
    internal::cs_create_with_spincount( m_mutex, m_spin_count );
}
inline mutex::mutex(const mutex& o)
    : m_spin_count(o.m_spin_count), m_locked(o.m_locked)
{
    internal::cs_create_with_spincount( m_mutex, m_spin_count );
    // copy state
    if      (  o.is_locked() && !m_locked ) lock();
    else if ( !o.is_locked() &&  m_locked ) unlock();
}
inline mutex::~mutex() {
    internal::cs_destroy( m_mutex );
}

// thread functions
inline bool mutex::lock() {
    m_locked = true;
    internal::cs_lock( m_mutex );
    return true;
}
inline bool mutex::try_lock() {
    m_locked = true;
    return internal::cs_try_lock( m_mutex );
}
inline bool mutex::unlock() {
    m_locked = false;
    internal::cs_unlock( m_mutex );
    return true;
}
inline bool mutex::is_locked() const {
    return m_locked;
}

// mutator functions
inline const mutex& mutex::operator =(const mutex& o) {
    set_spin_count( o.get_spin_count() );
    if      (  o.is_locked() && !m_locked) lock();
    else if ( !o.is_locked() &&  m_locked) unlock();
    return (*this);
}
inline void mutex::set_spin_count(uint32_t spin_count) {
    m_spin_count = spin_count;
    internal::cs_set_spincount( m_mutex, m_spin_count );
}
inline uint32_t mutex::get_spin_count() const {
    return m_spin_count;
}

// ------------------------------------------------------------------------- //
// Mutex Holder                                                              //
// ------------------------------------------------------------------------- //
// constructors
inline mutex_holder::mutex_holder( mutex& m ) : m_mutex_ptr( &m ) {
    m_mutex_ptr->lock();
}
inline mutex_holder::~mutex_holder() {
    if (m_mutex_ptr != NULL) m_mutex_ptr->unlock();
}
// early release
inline void mutex_holder::release() {
    m_mutex_ptr->unlock();
    m_mutex_ptr = NULL;
}

// ------------------------------------------------------------------------- //
// Semaphore                                                                 //
// ------------------------------------------------------------------------- //
// constructors
inline semaphore::semaphore(int32_t init, int32_t max_count) : m_max_count(max_count) {
    m_handle = CreateSemaphore( NULL, init, m_max_count, NULL );
}
inline semaphore::semaphore(const semaphore& o) : m_max_count(o.m_max_count) {
    int32_t value = o.value();
    m_handle = CreateSemaphore( NULL, value, m_max_count,  NULL );
}
inline semaphore::~semaphore() {
    CloseHandle( m_handle );
}

// thread functions
inline bool semaphore::wait(uint32_t ms) const {
    return WaitForSingleObject( m_handle, ms ) == WAIT_OBJECT_0;
}
inline bool semaphore::release() {
    return ReleaseSemaphore( m_handle, 1, 0 ) != 0;
}
inline int32_t semaphore::value() const {
    long value = -1;
    ReleaseSemaphore( m_handle, 0, &value );
    return value;
}
inline void semaphore::reset(int32_t init) {
    CloseHandle( m_handle );
    m_handle = CreateSemaphore( NULL, init, m_max_count, NULL );
}

// mutator functions
inline const semaphore& semaphore::operator =(const semaphore& o) {
    reset( o.value() );
}

// ------------------------------------------------------------------------- //
// Thread                                                                    //
// ------------------------------------------------------------------------- //
// create
inline thread thread::fork() {
    return thread(m_process_mask);
}

inline thread::thread(const affinity_mask& affinity_mask) : m_handle(NULL), m_running(false), m_process_mask(affinity_mask), m_thread_mask(affinity_mask) {}

inline bool thread::start() {
    if ( m_running ) return false;
    m_handle = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) thread::entry_point, static_cast<void*>(this), 0, NULL);
    return m_handle != NULL;
}
inline bool thread::wait(uint32_t ms) const {
    if ( !m_running) return false;
    return WaitForSingleObject( m_handle, ms ) == WAIT_OBJECT_0;
}
inline bool thread::kill() {
    if ( !m_running ) return false;

    bool success = ( TerminateThread( m_handle, 1 ) != 0 ) && CloseHandle( m_handle );
    m_handle = 0x00;
    return success;
}

// attributes
inline bool thread::is_running() const { return m_running; }

// thread affinity mask (tam)
inline void thread::set_thread_affinity_mask(const affinity_mask& affinity_mask) {
    l_assert_msg( affinity_mask.test_subset(m_process_mask), "[thread] Invalid thread affinity mask" );

    if (SetThreadAffinityMask(m_handle, affinity_mask.get_affinity_mask()))
        m_thread_mask = affinity_mask;
}
inline const affinity_mask& thread::get_thread_affinity_mask() const { return m_thread_mask; }
inline void thread::reset_thread_affinity_mask() { set_thread_affinity_mask(m_process_mask); }
inline void thread::inherit_process_affinity_mask() {
    affinity_mask process_affinity_mask;
    if (get_process_affinity(&process_affinity_mask, NULL) == GEA_OK)
        m_process_mask = m_thread_mask = process_affinity_mask;
}

} // namespace gea //
