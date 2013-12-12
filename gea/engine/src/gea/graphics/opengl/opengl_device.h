#ifndef __GEA_OPENGL_DEVICE_H__
#define __GEA_OPENGL_DEVICE_H__

#include <gea/engine/system/window_win32.h>

namespace gea {
namespace gl3 {

//FIX: this should be moved to windows only branch
// ------------------------------------------------------------------------- //
// OpenGL Extension                                                          //
// ------------------------------------------------------------------------- //
class opengl_extension : public message_extension {
public:
    virtual ~opengl_extension() {}
    virtual LRESULT interpret_message(LPMSG msg);
private:
    LRESULT wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

    void configure_pixelformat(HWND hwnd);
};

} // namespace gl3 //
} // namespace gea //

#endif // __GEA_OPENGL_DEVICE_H__ //