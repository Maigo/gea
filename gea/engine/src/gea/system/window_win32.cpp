
#include <gea/engine/system/memory.h>

#include "window_win32.h"

namespace gea {

// ------------------------------------------------------------------------- //
// Window                                                                    //
// ------------------------------------------------------------------------- //
window::window(HINSTANCE hinstance) : m_listener(NULL), m_is_running(true), m_hinstance(hinstance) {}
window::~window() {}

bool window::register_class() {
    WNDCLASSEX wnd_class;
    mem::zero_memory( &wnd_class, sizeof(wnd_class) );

    // fill out the window class structure
    wnd_class.cbSize        = sizeof(wnd_class);
    wnd_class.style         = CS_HREDRAW | CS_VREDRAW;
    wnd_class.lpfnWndProc   = window::cb_wndproc;     // static method as the event handler
    wnd_class.cbClsExtra    = 0;
    wnd_class.cbWndExtra    = 0;
    wnd_class.hInstance     = m_hinstance;
    wnd_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);  // default icon
    wnd_class.hCursor       = LoadCursor(NULL, IDC_ARROW);      // default arrow
    wnd_class.hbrBackground = NULL;                             // don't need background
    wnd_class.lpszMenuName  = NULL;                             // no menu
    wnd_class.lpszClassName = L"TEST_APPLICATION";
    wnd_class.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

    return RegisterClassEx( &wnd_class ) != 0;
}

bool window::unregister_class() {
    return UnregisterClass( L"TEST_APPLICATION", m_hinstance ) != 0;
}

bool window::create(int nCmdShow) {
    int32_t m_x = 0, m_y = 0, m_height = 600, m_width = 800;

    DWORD   dwExStyle;       // Window Extended Style
    DWORD   dwStyle;         // Window Style

    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // windows extended style
    dwStyle   = WS_OVERLAPPEDWINDOW;                  // windows style

    RECT rc;
    rc.left   = (LONG) m_x;            // set left value to 0
    rc.right  = (LONG) m_x + m_width;  // set right value to requested width
    rc.top    = (LONG) m_y;            // set top value to 0
    rc.bottom = (LONG) m_y + m_height; // set bottom value to requested height

    AdjustWindowRectEx(&rc, dwStyle, false, dwExStyle);   // adjust window to true requested size

    HWND hwnd = CreateWindowEx(NULL,                // extended style
        L"TEST_APPLICATION",                        // class name
        L"GEA Application",                         // app name
        dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        0, 0,                                       // x,y coordinate
        rc.right - rc.left,
        rc.bottom - rc.top,     // width, height
        NULL,                                       // handle to parent
        NULL,                                       // handle to menu
        m_hinstance,                                // application instance
        this);                                      // we pass a pointer to the window here

    // check if window creation failed (hwnd would equal NULL)
    if ( hwnd == NULL )
        return false;

    // store this reference
    SetWindowLong(hwnd, GWL_USERDATA, reinterpret_cast<long>(this));

    ShowWindow(hwnd, nCmdShow); // display the window
    UpdateWindow(hwnd);         // update the window

    return true;
}

void window::add_extension( message_extension* mex ) {
    m_listener = mex;
}
void window::del_extension( message_extension* mex ) {
    m_listener = NULL;
}

void window::update() {

    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if ( delegate_message( &msg ) != 0 ) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void window::on_paint(HWND hwnd, HDC hdc) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	PAINTSTRUCT ps;
    HDC dc = BeginPaint(hwnd, &ps);
	HBRUSH brush = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	FillRect(dc, &rect, brush);
	EndPaint(hwnd, &ps);
}

// ------------------------------------------------------------------------- //

LRESULT window::delegate_message(LPMSG msg) {
    //TODO: support more than one listener
    return (m_listener != NULL) ? m_listener->interpret_message(msg) : TRUE;
}

LRESULT CALLBACK window::wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
    case WM_CREATE:             // window creation
        break;
	case WM_MOVE:	
		on_move( (int32_t) LOWORD(lparam), (int32_t) HIWORD(lparam));		
		break;
    case WM_SIZE: {
		RECT rc;
		GetClientRect( hwnd, &rc );
		on_size( (int32_t) rc.right, (int32_t) rc.bottom);
		break; }
    case WM_PAINT:
        on_paint(hwnd, reinterpret_cast<HDC>(wparam));
        break;
    case WM_DESTROY: // window destroy
    case WM_CLOSE: // windows is closing
		show_window(hwnd, false);
        on_close();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	return 0;
}

} // namespace gea //
