namespace gea {

template <int N>
static void push_vertices(ren::vertex2_color (&vertices)[N], std::vector<ren::vertex2_color> &out_vertices) {
    out_vertices.reserve(out_vertices.size() + N);
    for (int i = 0; i < N; ++i)
        out_vertices.push_back(vertices[i]);
}

// ------------------------------------------------------------------------- //
// glfw_immediate_renderer                                                   //
// ------------------------------------------------------------------------- //

inline glfw_immediate_renderer::glfw_immediate_renderer() : m_color() {}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::push_transform(const mth::linear_transform2 &transform) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::pop_transform() {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline const mth::linear_transform2 &glfw_immediate_renderer::peek_transform() const {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_color(const mth::color &c) {
    m_color = c;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_point(const mth::point2 &point) {
    ren::vertex2_color v[6];
    ren::primitive_square(4, m_color.data, v);

    const uint32_t index = m_vertices.size();
    push_vertices(v, m_vertices);

    m_render_ops.push_back(create_draw_vertices_op(index, index + 6));
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_point(const std::vector<mth::point2> &points) {
    for (const mth::point2 &point : points) {
        draw_point(point);
    }
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_line(const mth::line2 &line) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_line(const std::vector<mth::line2> &lines) {
    for (const mth::line2 &line : lines) {
        draw_line(line);
    }
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_rectangle(const mth::rectangle2 &rectangle) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_rectangle(const std::vector<mth::rectangle2> &rectangles) {
    for (const mth::rectangle2 &rectangle : rectangles) {
        draw_rectangle(rectangle);
    }
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_polygon(const mth::polygon2 &polygon) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::draw_polygon(const std::vector<mth::polygon2> &polygons) {
    for (const mth::polygon2 &polygon : polygons) {
        draw_polygon(polygon);
    }
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::fill_point(const mth::point2 &point) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::fill_point(const std::vector<mth::point2> &points) {
    for (const mth::point2 &point : points) {
        fill_point(point);
    }
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::fill_rectangle(const mth::rectangle2 &rectangle) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::fill_rectangle(const std::vector<mth::rectangle2> &rectangles) {
    for (const mth::rectangle2 &rectangle : rectangles) {
        fill_rectangle(rectangle);
    }
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::clear() {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //

inline void glfw_immediate_renderer::flush() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, ren::vertex2_color::position_stride, &m_vertices.front() + ren::vertex2_color::position_offset);
    glColorPointer(4, GL_UNSIGNED_INT, ren::vertex2_color::color_stride, &m_vertices.front() + ren::vertex2_color::color_offset);

//    asdasd
}

// ------------------------------------------------------------------------- //

} // namespace gea //
