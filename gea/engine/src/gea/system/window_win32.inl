
namespace gea {

// ------------------------------------------------------------------------- //
// Window                                                                    //
// ------------------------------------------------------------------------- //
inline bool window::is_running() const { return m_is_running; }

inline void window::show_window(HWND hwnd, bool enable) {
    ShowWindow(hwnd, enable ? SW_SHOW : SW_HIDE);
    UpdateWindow(hwnd);
}

inline void window::show_cursor(HWND hwnd, bool enable) {

}

inline void window::on_move(int32_t x, int32_t y) {}
inline void window::on_size(int32_t width, int32_t height) {}
inline void window::on_close() { m_is_running = false; }

inline float window::aspect_ratio() const { return (float) width() / (float) height(); }
inline int32_t window::width()  const { return 1;  }
inline int32_t window::height() const { return 1; }

inline LRESULT CALLBACK window::cb_wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	window* win = reinterpret_cast<window*>( GetWindowLong(hwnd, GWL_USERDATA) );
    if( win != NULL ) return win->wndproc( hwnd, umsg, wparam, lparam );
    else              return DefWindowProc( hwnd, umsg, wparam, lparam );
}

} // namespace gea //