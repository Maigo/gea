
namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// semaphore                                                                 //
// ------------------------------------------------------------------------- //
// constructors
inline semaphore::semaphore(int32_t init, int32_t max_count) : m_max_count(max_count) {
    internal::semaphore_create( m_semaphore, init, m_max_count );
}
inline semaphore::semaphore(const semaphore& o) : m_max_count(o.m_max_count) {
    int32_t value = o.value();
    internal::semaphore_create( m_semaphore, value, m_max_count );
}
inline semaphore::~semaphore() {
    internal::semaphore_destroy( m_semaphore );
}

// thread functions
inline bool semaphore::wait(uint32_t ms) {
    return internal::semaphore_wait( m_semaphore, ms );
}
inline bool semaphore::release() {
    return internal::semaphore_release( m_semaphore );
}
inline int32_t semaphore::value() const {
    return internal::semaphore_value( m_semaphore );
}
inline void semaphore::reset(int32_t init) {
    internal::semaphore_destroy( m_semaphore );
    internal::semaphore_create( m_semaphore, init, m_max_count );
}

// mutator functions
inline const semaphore& semaphore::operator =(const semaphore& o) {
    reset( o.value() );
}

} // namespace prl //
} // namespace gea //
