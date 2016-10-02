#ifndef __GEA_DEMO_CORE_SYSTEM_EVENT_H__
#define __GEA_DEMO_CORE_SYSTEM_EVENT_H__

namespace gea {

// ------------------------------------------------------------------------- //
// system_event                                                              //
// ------------------------------------------------------------------------- //

enum system_event_type {
    system_event_type__native,
    system_event_type__quit
};

// ------------------------------------------------------------------------- //

struct system_event {
    system_event_type type;
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
