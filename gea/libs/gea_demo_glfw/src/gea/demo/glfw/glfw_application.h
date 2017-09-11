#ifndef __GEA_DEMO_GLFW_APPLICATION_H__
#define __GEA_DEMO_GLFW_APPLICATION_H__

// gea includes
#include <gea/demo/core/core_application.h>
#include <gea/demo/glfw/callback/glfw_callback_handler.h>

// forward declarations
struct GLFWwindow;

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

    virtual void update() = 0;
    virtual void render(const render_context &context) override = 0;

    // glfw setup
    void create_window(int width, int height, const char *title);
    void destroy_window();

private:
    void onKeyInput(const system_event_key_input& event);
    void onWindowFocus(const system_event_window_focus& event);
    void onWindowResize(const system_event_window_resize& event);
    void onWindowQuit(const system_event_window_quit& event);


    glfw_callback_handler   m_callbacks;

    GLFWwindow*             m_window;
    bool                    m_quit;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // __GEA_DEMO_GLFW_APPLICATION_H__ //
