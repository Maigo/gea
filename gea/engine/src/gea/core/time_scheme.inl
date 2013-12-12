
namespace gea {

// ------------------------------------------------------------------------- //
// time_scheme                                                               //
// ------------------------------------------------------------------------- //
inline time_scheme::time_scheme() : mode_base(),
    m_dt_max(1.0f / FRAMERATE_MIN_DEFAULT),
    m_dt_min(1.0f / FRAMERATE_MAX_DEFAULT),
    m_wait_last_frame(0.0f)//,
//    m_window(FRAMERATE_WINDOW_SIZE_DEFAULT)
{}

inline void time_scheme::set_max_framerate(const time32_t &fps) {
    if (fps > 0.0f) {
        m_dt_min = 1.0f / fps;
        enable_mode(FRAMERATE_MAX);
    } else {
        disable_mode(FRAMERATE_MAX);
    }
}

inline void time_scheme::set_min_framerate(const time32_t &fps) {
    if (fps > 0.0f) {
        m_dt_max = 1.0f / fps;
        enable_mode(FRAMERATE_MIN);
    } else {
        disable_mode(FRAMERATE_MIN);
    }
}

inline void time_scheme::set_smooth_framerate(const uint32_t &window_size) {
    if (window_size > 0) {
        enable_mode(SMOOTH_FRAMERATES);
    } else {
        disable_mode(SMOOTH_FRAMERATES);
    }
}

} // namespace gea //
