#ifndef __GEA_DEMO_CORE_APPLICATION_H__
#define __GEA_DEMO_CORE_APPLICATION_H__

#include <gea/demo/core/event/system_event.h>

namespace gea {

// ------------------------------------------------------------------------- //
// core_application                                                          //
// ------------------------------------------------------------------------- //

struct window_info
{
    float width, height, ratio;
};

class render_context {
public:
    inline const window_info& get_window_info() const { return m_window_info; }
    inline void set_window_info(const window_info& window_info) { m_window_info = window_info; }

private:
    window_info m_window_info;
};

// ------------------------------------------------------------------------- //

class core_application : public system_event_listener {
public:
    int app_main(int argc, char *argv[]);

    core_application();
    virtual ~core_application();

protected:
    virtual void initialize();
    virtual void main_loop();
    virtual void deinitialize();

    virtual void event(const system_event &event) override;

    virtual void render(const render_context &context) = 0;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_CORE_APPLICATION_H__ //
