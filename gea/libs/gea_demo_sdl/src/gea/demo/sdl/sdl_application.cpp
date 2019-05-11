// header include
#include "sdl_application.h"

namespace gea {

// ------------------------------------------------------------------------- //
// sdl_application                                                           //
// ------------------------------------------------------------------------- //

sdl_application::sdl_application() : super_t(), m_event_pump(this), m_quit(false) {}

// ------------------------------------------------------------------------- //

sdl_application::~sdl_application() {}

// ------------------------------------------------------------------------- //

void sdl_application::initialize(const init_info& info) {
    super_t::initialize(info);
}

// ------------------------------------------------------------------------- //

void sdl_application::main_loop() {
    render_context context;

    while (!m_quit) {
        // render
        render(context);

        // handle system events
        m_event_pump.flush();
    }
}

// ------------------------------------------------------------------------- //

void sdl_application::deinitialize(const deinit_info& info) {
    super_t::deinitialize(info);
}

// ------------------------------------------------------------------------- //

void sdl_application::event(const system_event &event) {
    switch (event.type) {
    case system_event_type__window_focus:
        // do something maybe
        break;
    case system_event_type__window_quit:
        m_quit = true;
        break;
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
