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
    void callback_error(int error, const char* description);
    void callback_close(const GLFWwindow* window);
    void callback_focus(const GLFWwindow* window, int focused);

private:
    system_event_listener* m_listener;
};

// ------------------------------------------------------------------------- //

}

#endif // __GEA_DEMO_GLFW_CALLBACK_HANDLER_H__ //
