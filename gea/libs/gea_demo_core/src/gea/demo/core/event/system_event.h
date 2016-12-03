#ifndef __GEA_DEMO_CORE_SYSTEM_EVENT_H__
#define __GEA_DEMO_CORE_SYSTEM_EVENT_H__

namespace gea {

// ------------------------------------------------------------------------- //
// system_event                                                              //
// ------------------------------------------------------------------------- //

enum system_event_type {
    system_event_type__window_focus,
    system_event_type__window_quit
};

// ------------------------------------------------------------------------- //

struct system_event_window_focus {
    bool has_focus;
};
struct system_event_window_quit {};

// ------------------------------------------------------------------------- //

struct system_event {
    system_event_type type;
    union {
        system_event_window_focus   window_focus;
        system_event_window_quit    window_quit;
    };
};

// ------------------------------------------------------------------------- //
// system_event_listener                                                     //
// ------------------------------------------------------------------------- //

class system_event_listener {
public:
    virtual void event(const system_event &event) = 0;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_CORE_SYSTEM_EVENT_H__ //
