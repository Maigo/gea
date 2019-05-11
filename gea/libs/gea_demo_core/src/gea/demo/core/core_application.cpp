// header include
#include "core_application.h"

namespace gea {

// ------------------------------------------------------------------------- //
// core application                                                          //
// ------------------------------------------------------------------------- //

static inline void construct_init_info(const int argc, const char** argv, init_info& out) {
    out = { argc, argv };
}
static inline void construct_deinit_info(deinit_info& out) {
}

// ------------------------------------------------------------------------- //

core_application::core_application() {}

// ------------------------------------------------------------------------- //

core_application::~core_application() {}

// ------------------------------------------------------------------------- //

int core_application::app_main(const int argc, const char** argv) {
    init_info init_info;
    construct_init_info(argc, argv, init_info);

    deinit_info deinit_info;
    construct_deinit_info(deinit_info);

    initialize(init_info);
    main_loop();
    deinitialize(deinit_info);

    return 0;
}

// ------------------------------------------------------------------------- //

void core_application::initialize(const init_info& info) {}

// ------------------------------------------------------------------------- //

void core_application::main_loop() {}

// ------------------------------------------------------------------------- //

void core_application::deinitialize(const deinit_info& info) {}

// ------------------------------------------------------------------------- //

void core_application::event(const system_event &event) {}

// ------------------------------------------------------------------------- //

} // namespace gea //
