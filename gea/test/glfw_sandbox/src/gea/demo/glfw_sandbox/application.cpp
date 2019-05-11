// header include
#include "application.h"

// glfw includes
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <glad/glad.h>
#include <glfw/glfw3.h>

// gea includes
#include <gea/mth_vector/matrix4.h>
#include <gea/mth_visual/linear_transforms.h>

namespace gea {

// ------------------------------------------------------------------------- //
// DATA                                                                      //
// ------------------------------------------------------------------------- //

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    { 0.6f, -0.4f, 0.f, 1.f, 0.f },
    { 0.f, 0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =                 \
    "uniform mat4 MVP;\n"                               \
    "attribute vec3 vCol;\n"                            \
    "attribute vec2 vPos;\n"                            \
    "varying vec3 color;\n"                             \
    "void main()\n"                                     \
    "{\n"                                               \
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"   \
    "    color = vCol;\n"                               \
    "}\n";

static const char* fragment_shader_text =               \
    "varying vec3 color;\n"                             \
    "void main()\n"                                     \
    "{\n"                                               \
    "    gl_FragColor = vec4(color, 1.0);\n"            \
    "}\n";

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

application::application() : super_t(), m_program(0) {}

// ------------------------------------------------------------------------- //

void application::initialize(const init_info& info) {
    super_t::initialize(info);

    create_window(SCREEN_WIDTH, SCREEN_HEIGHT, "demo: glfw_sandbox");

    // get window renderer

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    m_program = program;
}

// ------------------------------------------------------------------------- //

void application::deinitialize(const deinit_info& info) {
    destroy_window();

    super_t::deinitialize(info);
};

// ------------------------------------------------------------------------- //

void application::update() {
}

// ------------------------------------------------------------------------- //

void application::render(const render_context &context) {
    glClear(GL_COLOR_BUFFER_BIT);

    const window_info& window_info = context.get_window_info();
    const float ratio = window_info.ratio;

    mth::mat4 m(mth::SKIP_INITIALIZATION), p(mth::SKIP_INITIALIZATION), mvp(mth::SKIP_INITIALIZATION);
    mth::rotation_matrix(2*float(glfwGetTime()), mth::vec3::Z_AXIS, m);
    mth::orthogonal_matrix(-ratio, ratio, -1.f, 1.f, 1.f, -1.f, p);
    mvp = m * p;

    GLint mvp_location, vpos_location, vcol_location;
    mvp_location = glGetUniformLocation(m_program, "MVP");
    vpos_location = glGetAttribLocation(m_program, "vPos");
    vcol_location = glGetAttribLocation(m_program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(float) * 5, (void*)(sizeof(float) * 2));

    glUseProgram(m_program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(mvp.m));
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
