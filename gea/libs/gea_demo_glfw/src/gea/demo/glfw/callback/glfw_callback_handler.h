#ifndef __GEA_DEMO_GLFW_CALLBACK_HANDLER_H__
#define __GEA_DEMO_GLFW_CALLBACK_HANDLER_H__

// forward declarations
struct GLFWwindow;

namespace gea {

class system_event_listener;

// ------------------------------------------------------------------------- //
// glfw_callback_handler                                                     //
// ------------------------------------------------------------------------- //

class glfw_callback_handler {
public:
    glfw_callback_handler(system_event_listener* listener);

    // glfw callbacks
    void callback_error(const int error, const char* const description);
    void callback_close(const GLFWwindow* const window);
    void callback_focus(const GLFWwindow* const window, const int focused);
    void callback_resize(const GLFWwindow* const window, const int width, const int height);
    void callback_key(const GLFWwindow* window, const int key, const int scancode, const int action, const int mods);

private:
    system_event_listener* m_listener;
};

// ------------------------------------------------------------------------- //

}

#endif // __GEA_DEMO_GLFW_CALLBACK_HANDLER_H__ //
