
// std includes
#include <stdio.h>
// gea includes
#include <gea/utility/timer.h>
// * managers
//#include <gea/system/info/cpu.h>
//#include <gea/core/parallel/task_manager.h>

// header include
#include "application.h"

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //
void application::init_managers() {
    // memory manager


    // timer manager
    timer_manager::construct();

    // cpu manager
//    cpu::cpu_manager::construct();
    // task manager
//    prl::task_manager::construct();
}

void application::run() {
    // setup
    m_time_scheme.set_max_framerate(60.0f);
    m_time_scheme.set_min_framerate(24.0f);
//    _time_scheme.set_smooth_framerate(10); // broken :(

    while (!m_quit) {
        update();
    }

    // tear down
}

void application::update() {
    // get passed time
    timer_manager &time_mgr = timer_manager::get();
    time_mgr.update();

    time32_t delta_time = time_mgr.get_delta_time();
             delta_time = m_time_scheme.update(delta_time);

    // do something
    printf("frame: %i - %.2f fps (dt %.4fms)\n", time_mgr.get_current_frame(), (1.0f / delta_time), delta_time * 1000.0f);
}

} // namespace gea //
