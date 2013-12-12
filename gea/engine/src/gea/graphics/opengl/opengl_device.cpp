
// gea includes
#include <gea/engine/system/memory.h>
#include <gea/engine/system/platform.h>

// opengl includes
#include <GL/gl.h>
#include <wglext.h>

#include "opengl_device.h"

// global defines
typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

namespace gea {
namespace gl3 {

LRESULT opengl_extension::interpret_message(LPMSG msg) {
    return wndproc( msg->hwnd, msg->message, msg->wParam, msg->lParam );
}

LRESULT opengl_extension::wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
    switch (umsg) {
    case WM_CREATE: {                   // window creation
        HDC hdc = GetDC(hwnd);
        configure_pixelformat(hwnd);

        // set the version that we want, in this case 3.0
        int attribs[] = {
	        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	        WGL_CONTEXT_MINOR_VERSION_ARB, 0,
        0 }; // zero indicates the end of the array

        // create temporary context so we can get a pointer to the function
        HGLRC hglrc, tmpContext = wglCreateContext(hdc);
        // make it current
        wglMakeCurrent(hdc, tmpContext);

        // get the function pointer
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");

        // if this is NULL then OpenGL 3.0 is not supported
        if (!wglCreateContextAttribsARB) {
//			std::cerr << "OpenGL 3.0 is not supported, falling back to GL 2.1" << std::endl;
            hglrc = tmpContext;
        } 
		else
		{
			// create an OpenGL 3.0 context using the new function
			hglrc = wglCreateContextAttribsARB(hdc, 0, attribs);
			// delete the temporary context
			wglDeleteContext(tmpContext);
		}

        // make the GL3 context current
        wglMakeCurrent(hdc, hglrc);
        break; }
    case WM_CLOSE: {                    // windows is closing
        HDC hdc = GetDC(hwnd);
        HGLRC hglrc = wglGetCurrentContext();
        wglMakeCurrent(hdc, NULL);
        wglDeleteContext(hglrc);
        break; }
	default:
        // do nothing for unhandled messages
        break;
    }

	return TRUE;                       // fall through to default
}

void opengl_extension::configure_pixelformat(HWND hwnd) {
    HDC hdc = GetDC (hwnd);

    PIXELFORMATDESCRIPTOR pfd;
    mem::zero_memory( &pfd, sizeof(pfd) );

    pfd.nSize      = sizeof(pfd);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA;
    pfd.iPixelType = 32;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
}

} // namespace gl3 //
} // namespace gea //
