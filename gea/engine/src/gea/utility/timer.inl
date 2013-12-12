
namespace gea {

// ------------------------------------------------------------------------- //
// global_timer                                                              //
// ------------------------------------------------------------------------- //
inline global_timer::global_timer() {
    m_last = m_start = get_system_timestamp();
    m_frequency = get_system_frequency();
}

inline time32_t global_timer::time_since_last() {
    timestamp64_t time = m_last;
    m_last = get_system_timestamp();
    return static_cast<time32_t>(m_last - time) / static_cast<time32_t>(m_frequency);
}

// ------------------------------------------------------------------------- //
// timer_manager                                                             //
// ------------------------------------------------------------------------- //
inline timer_manager::timer_manager() : m_frame_count(0), m_delta_time(0) {}

inline global_timer& timer_manager::get_global_timer() { return m_global_timer; }

inline uint32_t timer_manager::get_current_frame() const { return m_frame_count; }

inline void timer_manager::update() {
    ++m_frame_count;
    m_delta_time = m_global_timer.time_since_last();
}
inline time32_t timer_manager::get_delta_time() const { return m_delta_time; }

} // namespace gea //
