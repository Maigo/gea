#ifndef __GEA_DEMO_RENDER_QUEUE_H__
#define __GEA_DEMO_RENDER_QUEUE_H__

// std includes
#include <vector>

namespace gea {

// ------------------------------------------------------------------------- //
// render_queue                                                              //
// ------------------------------------------------------------------------- //

enum render_queue_op_type {
    render_queue_op_type__invalid,
    render_queue_op_type__set_shader_program,
    render_queue_op_type__set_texture,
    render_queue_op_type__draw_vertices,

    render_queue_op_type_count,
};

struct set_shader_program_op {
    void *program;
};

struct set_texture_op {
    void *texture;
    int texture_unit;
};

enum render_queue_vertex_type {
    render_queue_vertex_type__vertex,
    render_queue_vertex_type__vertex_color,

    render_queue_vertex_type_count,
};

struct draw_vertices_op {
    uint16_t i0, i1;
};

struct render_queue_op {
    render_queue_op_type type;

    union {
        set_shader_program_op   set_shader_program;
        set_texture_op          set_texture;
        draw_vertices_op        draw_vertices;
    };
};

// ------------------------------------------------------------------------- //

inline render_queue_op create_set_shader_program_op(void *program);

inline render_queue_op create_set_texture_op(void *texture, int texture_unit);

inline render_queue_op create_draw_vertices_op(uint16_t i0, uint16_t i1);

// ------------------------------------------------------------------------- //

typedef std::vector<render_queue_op> render_queue;

} // namespace gea //

#include "render_queue.inl"

#endif // __GEA_DEMO_RENDER_QUEUE_H__ //
