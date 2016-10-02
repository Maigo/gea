#ifndef __GEA_DEMO_SDL_SYSTEM_EVENT_PUMP_H__
#define __GEA_DEMO_SDL_SYSTEM_EVENT_PUMP_H__

#include <gea\demo\core\event\system_event_pump.h>

namespace gea {

class system_event_listener;

// ------------------------------------------------------------------------- //
// sdl_system_event_pump                                                     //
// ------------------------------------------------------------------------- //

class sdl_system_event_pump : public system_event_pump {
public:
    sdl_system_event_pump(system_event_listener *listener);
    virtual ~sdl_system_event_pump();

    virtual const bool poll();
};

// ------------------------------------------------------------------------- //

}

#endif // __GEA_DEMO_SDL_SYSTEM_EVENT_PUMP_H__ //
