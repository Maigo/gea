namespace gea {

// ------------------------------------------------------------------------- //

inline render_queue_op create_set_shader_program_op(void *program) {
    render_queue_op op;
    op.type = render_queue_op_type__set_shader_program;
    op.set_shader_program.program = program;
    return op;
}

// ------------------------------------------------------------------------- //

inline render_queue_op create_set_texture_op(void *texture, int texture_unit) {
    render_queue_op op;
    op.type = render_queue_op_type__set_texture;
    op.set_texture.texture = texture;
    op.set_texture.texture_unit = texture_unit;
    return op;
}

// ------------------------------------------------------------------------- //

inline render_queue_op create_draw_vertices_op(uint16_t i0, uint16_t i1) {
    render_queue_op op;
    op.type = render_queue_op_type__draw_vertices;
    op.draw_vertices.i0 = i0;
    op.draw_vertices.i1 = i1;
    return op;
}

// ------------------------------------------------------------------------- //

}