#ifndef __GEA_TIMER_H__
#define __GEA_TIMER_H__

#include <gea/system/platform.h>
#include <gea/core/pattern/singleton.h>

namespace gea {

// ------------------------------------------------------------------------- //
// global_timer                                                              //
// ------------------------------------------------------------------------- //
class global_timer {
public:
    inline global_timer();

    inline time32_t time_since_last();

private:
    timestamp64_t m_start, m_last;
	frequency_t   m_frequency;
};

// ------------------------------------------------------------------------- //
// timer_manager                                                             //
// ------------------------------------------------------------------------- //
class timer_manager : public singleton<timer_manager> {
public:
    inline timer_manager();

    // timer access
    inline global_timer &get_global_timer();

    inline uint32_t get_current_frame() const;

    inline void update();
    inline time32_t get_delta_time() const;

    void update(time32_t delta_time) {}

private:
    uint32_t m_frame_count;
    time32_t m_delta_time;

    // timers
    global_timer m_global_timer;
};

} // namespace gea //

#include "timer.inl"

#endif // __GEA_TIMER_H__ //
