#ifndef __GEA_DEMO_APPLICATION_H__
#define __GEA_DEMO_APPLICATION_H__

// std includes
#include <vector>

// gea includes
#include <gea/demo/glfw/glfw_application.h>

// forward declarations
struct GLFWwindow;

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

class application : public glfw_application {
public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    typedef glfw_application super_t;

    application();
    virtual ~application();

protected:
    virtual void initialize() override;
    virtual void deinitialize() override;

    virtual void update() override;
    virtual void render(const render_context &context) override;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_APPLICATION_H__ //
