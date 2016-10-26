//header include
#include "system_event_pump.h"

// gea includes
#include <gea/demo/core/event/system_event.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// system_event_pump                                                         //
// ------------------------------------------------------------------------- //

system_event_pump::system_event_pump(system_event_listener *listener) : m_listener(listener) {
    l_assert_msg((m_listener != nullptr), "invalid event listener!");
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
