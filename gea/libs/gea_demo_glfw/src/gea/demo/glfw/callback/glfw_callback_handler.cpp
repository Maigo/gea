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

void glfw_callback_handler::callback_error(const int error, const char* const description) {
    l_assert_msg(false, description);
}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_close(const GLFWwindow* const window) {
    system_event event = { system_event_type__window_quit };
    m_listener->event(event);
}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_focus(const GLFWwindow* const window, const int focused) {
    system_event event = { system_event_type__window_focus };
    event.window_focus.has_focus = (focused == GLFW_TRUE);
    m_listener->event(event);
}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_resize(const GLFWwindow* const window, const int width, const int height)
{
    system_event event = { system_event_type__window_resize };
    event.window_resize.width = width;
    event.window_resize.height = height;
    m_listener->event(event);
}

// ------------------------------------------------------------------------- //

void glfw_callback_handler::callback_key(const GLFWwindow* const window, const int key, const int scancode, const int action, const int mods) {
    system_event event = { system_event_type__invalid };
    switch (action)
    {
    case GLFW_PRESS:
        event.type = system_event_type__key_down;
        event.key_input = (system_event_key_input){ uint32_t(key), uint32_t(scancode), uint16_t(mods) };
        break;
    case GLFW_RELEASE:
        event.type = system_event_type__key_up;
        event.key_input = (system_event_key_input){ uint32_t(key), uint32_t(scancode), uint16_t(mods) };
        break;
    case GLFW_REPEAT:
        event.type = system_event_type__key_repeat;
        event.key_input = (system_event_key_input){ uint32_t(key), uint32_t(scancode), uint16_t(mods) };
        break;
    default:
        l_assert_msg(false, "invalid keyboard input action!");
        return;
    }

    if (event.type != system_event_type__invalid) {
        m_listener->event(event);
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
