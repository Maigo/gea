#ifndef __GEA_DEMO_CORE_SYSTEM_EVENT_H__
#define __GEA_DEMO_CORE_SYSTEM_EVENT_H__

namespace gea {

// ------------------------------------------------------------------------- //
// system_event                                                              //
// ------------------------------------------------------------------------- //

enum system_event_type {
    system_event_type__key_up,
    system_event_type__key_repeat,
    system_event_type__key_down,
    system_event_type__window_focus,
    system_event_type__window_resize,
    system_event_type__window_quit,

    system_event_type__invalid
};

// ------------------------------------------------------------------------- //

struct system_event_key_input {
    uint32_t keycode;
    uint32_t scancode;
    uint16_t modifiers;
};
struct system_event_window_focus {
    bool has_focus;
};
struct system_event_window_resize {
    int32_t width;
    int32_t height;
};
struct system_event_window_quit {};

// ------------------------------------------------------------------------- //

struct system_event {
    system_event_type type;
    union {
        system_event_key_input      key_input;
        system_event_window_focus   window_focus;
        system_event_window_resize  window_resize;
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
