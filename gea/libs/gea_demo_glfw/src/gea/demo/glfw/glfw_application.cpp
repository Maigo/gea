// header include 
#include "glfw_application.h"

// gea includes
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// glfw_application                                                          //
// ------------------------------------------------------------------------- //

glfw_application::glfw_application() : super_t() {}

// ------------------------------------------------------------------------- //

glfw_application::~glfw_application() {}

// ------------------------------------------------------------------------- //

void glfw_application::initialize() {
    super_t::initialize();
}

// ------------------------------------------------------------------------- //

void glfw_application::main_loop() {
    render_context context;

    while (!m_quit) {
        // render
        render(context);

        // handle system events
        l_assert_implement;
    }
}

// ------------------------------------------------------------------------- //

void glfw_application::deinitialize() {
    super_t::deinitialize();
}

// ------------------------------------------------------------------------- //

void glfw_application::event(const system_event &event) {
    switch (event.type) {
    case system_event_type__quit:
        m_quit = true;
        break;
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
