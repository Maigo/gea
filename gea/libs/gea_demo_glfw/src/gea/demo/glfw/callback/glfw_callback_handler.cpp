// header include
#include "glfw_callback_handler.h"

// glfw includes
#include <glad/glad.h>
#include <glfw/glfw3.h>

// gea includes
#include <gea/demo/core/event/system_event.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// glfw_callback_handler                                                     //
// ------------------------------------------------------------------------- //

glfw_callback_handler::glfw_callback_handler(system_event_listener *listener) : m_listener(listener) {}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_error(int error, const char* description) {
    l_assert(false);
}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_close(const GLFWwindow* window) {
    system_event event = { system_event_type__window_quit };
    m_listener->event(event);
}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_focus(const GLFWwindow* window, int focused) {
    system_event event = { system_event_type__window_focus };
    event.window_focus.has_focus = (focused == GLFW_TRUE);
    m_listener->event(event);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
