// header include 
#include "application.h"

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

application::application() : super_t() {}

// ------------------------------------------------------------------------- //

application::~application() {}

// ------------------------------------------------------------------------- //

void application::initialize() {
    super_t::initialize();

    create_window(SCREEN_WIDTH, SCREEN_HEIGHT, "demo: glfw_sandbox");
}

// ------------------------------------------------------------------------- //

void application::deinitialize() {
    destroy_window();

    super_t::deinitialize();
};

// ------------------------------------------------------------------------- //

void application::update() {
}

// ------------------------------------------------------------------------- //

void application::render(const render_context &context) {}

// ------------------------------------------------------------------------- //

} // namespace gea //
