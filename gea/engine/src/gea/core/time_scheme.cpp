// header include
#include "time_scheme.h"

// gea includes
#include <gea/utility/assert.h>
#include <gea/utility/math.h>

namespace gea {

// ------------------------------------------------------------------------- //
// time_scheme                                                               //
// ------------------------------------------------------------------------- //
const time32_t time_scheme::FRAMERATE_MAX_DEFAULT         = 60.0f;
const time32_t time_scheme::FRAMERATE_MAX_DISABLE         = -1.0f;
const time32_t time_scheme::FRAMERATE_MIN_DEFAULT         = 24.0f;
const time32_t time_scheme::FRAMERATE_MIN_DISABLE         = -1.0f;
const uint32_t time_scheme::FRAMERATE_WINDOW_SIZE_DEFAULT =    10;
const uint32_t time_scheme::FRAMERATE_WINDOW_SIZE_DISABLE =     0;

time32_t time_scheme::update(time32_t raw_delta_time) {
    l_assert_msg(raw_delta_time > 0.0, "Negatime time step!\n"); // can this really happen?

    time32_t delta_time = raw_delta_time;

    // cap time step
    if ( is_mode(FRAMERATE_MIN) ) {
        delta_time = math::max(delta_time, m_dt_max);
    }

    // smooth frame rate
//    m_window.push_head(delta_time);
    if ( is_mode(SMOOTH_FRAMERATES) ) {
        //TODO: fix broken!
        l_assert_implement;
//      delta_time = math::mean( m_window.begin(), m_window.end() , (time32_t) 0.0f );
    }

    // cap framerate
    if ( is_mode(FRAMERATE_MAX) ) {
        m_wait_last_frame = m_dt_min - ( delta_time - m_wait_last_frame);
        if (m_wait_last_frame > 0) system_sleep_seconds( m_wait_last_frame );
    }

    // return modified delta
    return delta_time;
}

} // namespace gea //
