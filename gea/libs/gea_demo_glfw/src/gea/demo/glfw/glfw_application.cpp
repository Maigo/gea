// header include 
#include "glfw_application.h"

// glfw includes
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <glad/glad.h>
#include <glfw/glfw3.h>

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// glfw_application                                                          //
// ------------------------------------------------------------------------- //

glfw_application::glfw_application() : super_t(), m_callbacks(this), m_window(nullptr), m_quit(false) {}

// ------------------------------------------------------------------------- //

glfw_application::~glfw_application() {}

// ------------------------------------------------------------------------- //

void glfw_application::initialize() {
    super_t::initialize();

    // set global error callback
//    glfwSetErrorCallback((GLFWerrorfun)[this](int error, const char* description) { this->callback_error(error, description); });

    // initialize glfw
    if (glfwInit() != GLFW_TRUE) {
        printf("GLFW could not initialize!");
        return;
    }
}

// ------------------------------------------------------------------------- //

void glfw_application::main_loop() {
    render_context context;

    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    context.set_window_info((window_info){ float(width), float(height), float(width) / float(height) });

    while (!m_quit) {
        update();
        render(context);

        // swap buffers
        glfwSwapBuffers(m_window);

        // handle events
        glfwPollEvents();

        // check for termination
        if (glfwWindowShouldClose(m_window)) {
            m_quit = true;
        }
    }
}

// ------------------------------------------------------------------------- //

void glfw_application::deinitialize() {
    l_assert_msg(!m_window, "window must be destroyed!");

    glfwTerminate();

    super_t::deinitialize();
}

// ------------------------------------------------------------------------- //

void glfw_application::event(const system_event &event) {
    switch (event.type) {
    case system_event_type__key_up:
    case system_event_type__key_repeat:
    case system_event_type__key_down:
        onKeyInput(event.key_input);
        break;
    case system_event_type__window_focus:
        onWindowFocus(event.window_focus);
        break;
    case system_event_type__window_resize:
        onWindowResize(event.window_resize);
        break;
    case system_event_type__window_quit:
        onWindowQuit(event.window_quit);
        break;
    default:
        break;
    }
}

// ------------------------------------------------------------------------- //

void glfw_application::onKeyInput(const system_event_key_input& event)
{
    // do something maybe
}

// ------------------------------------------------------------------------- //

void glfw_application::onWindowFocus(const system_event_window_focus& event)
{
    // do something maybe
}

// ------------------------------------------------------------------------- //

void glfw_application::onWindowResize(const system_event_window_resize& event)
{
    glViewport(0, 0, event.width, event.height);
}

// ------------------------------------------------------------------------- //

void glfw_application::onWindowQuit(const system_event_window_quit& event)
{
    m_quit = true;
}

// ------------------------------------------------------------------------- //

void glfw_application::create_window(int width, int height, const char *title) {
    // create window
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_window == nullptr) {
        printf("Window could not be created!");
        return;
    }

    // set opengl context
    glfwMakeContextCurrent(m_window);

    // set context callbacks
    glfwSetWindowUserPointer(m_window, &m_callbacks);
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)->void { if (glfw_callback_handler* self = (glfw_callback_handler*)glfwGetWindowUserPointer(window)) { self->callback_close(window); }});
    glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused)->void { if (glfw_callback_handler* self = (glfw_callback_handler*)glfwGetWindowUserPointer(window)) { self->callback_focus(window, focused); }});
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)->void { if (glfw_callback_handler* self = (glfw_callback_handler*)glfwGetWindowUserPointer(window)) { self->callback_resize(window, width, height); }});
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)->void { if (glfw_callback_handler* self = (glfw_callback_handler*)glfwGetWindowUserPointer(window)) { self->callback_key(window, key, scancode, action, mods); }});

    // initialize extentions
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

// ------------------------------------------------------------------------- //

void glfw_application::destroy_window() {
    // unset context callbacks
    glfwSetWindowUserPointer(m_window, nullptr);
    glfwSetWindowCloseCallback(m_window, nullptr);
    glfwSetWindowFocusCallback(m_window, nullptr);

    // unset opengl context
    if (glfwGetCurrentContext() == m_window) {
        glfwMakeContextCurrent(nullptr);
    }

    // destroy window
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}


} // namespace gea //
