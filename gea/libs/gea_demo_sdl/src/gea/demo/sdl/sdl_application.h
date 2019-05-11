#ifndef __GEA_DEMO_SDL_APPLICATION_H__
#define __GEA_DEMO_SDL_APPLICATION_H__

#include <gea/demo/core/core_application.h>

#include <gea/demo/sdl/event/sdl_system_event_pump.h>

namespace gea {

// ------------------------------------------------------------------------- //
// sdl_application                                                           //
// ------------------------------------------------------------------------- //

class sdl_application : public core_application {
public:
    typedef core_application super_t;

    sdl_application();
    virtual ~sdl_application();

protected:
    virtual void initialize(const init_info& info) override;
    virtual void main_loop() override;
    virtual void deinitialize(const deinit_info& info) override;

    virtual void event(const system_event &event) override;

    virtual void render(const render_context &context) override = 0;

private:

    sdl_system_event_pump   m_event_pump;
    bool                    m_quit;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_SDL_APPLICATION_H__ //
