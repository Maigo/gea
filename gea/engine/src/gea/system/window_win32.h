#ifndef __GEA_WINDOW_WIN32_H__
#define __GEA_WINDOW_WIN32_H__

#include <gea/engine/system/platform.h>

namespace gea {

// ------------------------------------------------------------------------- //
// Message Extension                                                         //
// ------------------------------------------------------------------------- //
class message_extension {
public:
    virtual ~message_extension() {}
    virtual LRESULT interpret_message(LPMSG msg) = 0;
};

// ------------------------------------------------------------------------- //
// Window                                                                    //
// ------------------------------------------------------------------------- //
class window {
public:
    window(HINSTANCE hinstance);
    ~window();

    bool register_class();
    bool unregister_class();
    bool create(int nCmdShow = SW_SHOW);

    void add_extension( message_extension* mex );
    void del_extension( message_extension* mex );

    inline bool is_running() const;
    void update();

    inline void on_move(int32_t x, int32_t y);
    inline void on_size(int32_t width, int32_t height);
    inline void on_close();
    void on_paint(HWND hwnd, HDC hdc);

    inline void show_window(HWND hwnd, bool enable);
    inline void show_cursor(HWND hwnd, bool enable);

    inline float aspect_ratio() const;

    inline int32_t width() const;
    inline int32_t height() const;

    static inline LRESULT CALLBACK cb_wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
    LRESULT CALLBACK wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:
    LRESULT delegate_message(PMSG msg);
    message_extension* m_listener;

    // internal settings
//    bool        m_isFullscreen;
    bool        m_is_running;

    // windows stuff
    HINSTANCE   m_hinstance;    // application instance
};

} // namespace gea //

#include "window_win32.inl"

#endif // __GEA_WINDOW_WIN32_H__ //
