
//header include
#include "system_event_pump.h"

// std includes
#include <assert.h>

// gea includes
#include <gea\demo\core\event\system_event.h>

namespace gea {

// ------------------------------------------------------------------------- //
// system_event_pump                                                         //
// ------------------------------------------------------------------------- //

system_event_pump::system_event_pump(system_event_listener *listener) : m_listener(listener) {
    assert((m_listener != nullptr) && "invalid event listener!");
}

// ------------------------------------------------------------------------- //

system_event_pump::~system_event_pump() {}

// ------------------------------------------------------------------------- //

void system_event_pump::flush() {
    while (poll()) {}
}

// ------------------------------------------------------------------------- //

void system_event_pump::dispatch(const system_event &event) {
    if (m_listener != nullptr) {
        m_listener->event(event);
    }
}

// ------------------------------------------------------------------------- //

}
