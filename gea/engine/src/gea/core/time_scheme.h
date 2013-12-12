#ifndef __GEA_TIME_SCHEME_H__
#define __GEA_TIME_SCHEME_H__

// gea includes
//#include <core/collection/circular_buffer.h>
#include <gea/system/platform.h>
#include <gea/utility/state.h>

namespace gea {

// ------------------------------------------------------------------------- //
// time_scheme                                                               //
// ------------------------------------------------------------------------- //
class time_scheme : public utl::mode_base<uint32_t> {
public:
    static const time32_t FRAMERATE_MAX_DEFAULT, FRAMERATE_MAX_DISABLE;
    static const time32_t FRAMERATE_MIN_DEFAULT, FRAMERATE_MIN_DISABLE;
    static const uint32_t FRAMERATE_WINDOW_SIZE_DEFAULT, FRAMERATE_WINDOW_SIZE_DISABLE;

    enum modes { FRAMERATE_MAX = 0, FRAMERATE_MIN, SMOOTH_FRAMERATES };

    inline time_scheme();

    inline void set_max_framerate(const time32_t &fps);
    inline void set_min_framerate(const time32_t &fps);
    inline void set_smooth_framerate(const uint32_t &window_size);

    time32_t update(time32_t raw_delta_time);

private:
    time32_t m_dt_max;

    time32_t m_dt_min;
    time32_t m_wait_last_frame;

    //circular_buffer<time32_t> m_window;
};

} // namespace gea //

#include "time_scheme.inl"

#endif // __GEA_TIME_SCHEME_H__ //
