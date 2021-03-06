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
    virtual ~application() = default;

protected:
    virtual void initialize(const init_info& info) override;
            void initialize_shader();
    virtual void deinitialize(const deinit_info& info) override;

    virtual void update() override;
    virtual void render(const render_context &context) override;

private:
    unsigned int m_program;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_APPLICATION_H__ //
