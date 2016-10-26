
// header include
#include "core_application.h"

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

core_application::core_application() {}

// ------------------------------------------------------------------------- //

core_application::~core_application() {}

// ------------------------------------------------------------------------- //

int core_application::app_main(int argc, char *argv[]) {
    initialize();
    main_loop();
    deinitialize();

    return 0;
}

// ------------------------------------------------------------------------- //

void core_application::initialize() {}

// ------------------------------------------------------------------------- //

void core_application::main_loop() {}

// ------------------------------------------------------------------------- //

void core_application::deinitialize() {}

// ------------------------------------------------------------------------- //

void core_application::event(const system_event &event) {}

// ------------------------------------------------------------------------- //

} // namespace gea //
