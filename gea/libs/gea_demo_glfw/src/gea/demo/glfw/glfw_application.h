#ifndef __GEA_DEMO_GLFW_APPLICATION_H__
#define __GEA_DEMO_GLFW_APPLICATION_H__

// gea includes
#include <gea/demo/core/core_application.h>

namespace gea {

// ------------------------------------------------------------------------- //
// glfw_application                                                          //
// ------------------------------------------------------------------------- //

class glfw_application : public core_application {
public:
    typedef core_application super_t;

    glfw_application();
    virtual ~glfw_application();

protected:
    virtual void initialize() override;
    virtual void main_loop() override;
    virtual void deinitialize() override;

    virtual void event(const system_event &event) override;

    virtual void render(const render_context &context) override = 0;

private:
    bool                    m_quit;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_GLFW_APPLICATION_H__ //
