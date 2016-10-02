#ifndef __GEA_DEMO_APPLICATION_H__
#define __GEA_DEMO_APPLICATION_H__

// gea includes
#include <gea\demo\sdl\sdl_application.h>

#include <gea\mth_geometry\line.h>

struct SDL_Window;
struct SDL_Renderer;

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

class application : public sdl_application {
public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    typedef sdl_application super_t;

    application();
    virtual ~application();

protected:
    virtual void initialize() override;
    virtual void deinitialize() override;

    virtual void render(const render_context &context) override;

private:
    mth::line2      m_line;
    mth::line2      m_reducedLine;

    SDL_Window*     m_window;
    SDL_Renderer*   m_renderer;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_APPLICATION_H__ //