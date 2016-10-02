#ifndef __GEA_DEMO_CORE_SYSTEM_EVET_PUMP_H__
#define __GEA_DEMO_CORE_SYSTEM_EVET_PUMP_H__

namespace gea {

class system_event_listener;
struct system_event;

// ------------------------------------------------------------------------- //
// system_event_pump                                                         //
// ------------------------------------------------------------------------- //

class system_event_pump {
public:
    system_event_pump(system_event_listener *listener);
    virtual ~system_event_pump();

    virtual void flush();
    virtual const bool poll() = 0;

protected:
    void dispatch(const system_event &event);

private:
    system_event_listener *m_listener;
};

// ------------------------------------------------------------------------- //

}

#endif // __GEA_DEMO_CORE_SYSTEM_EVET_PUMP_H__ //
