
namespace gea {

// ------------------------------------------------------------------------- //
// sdl_immediate_renderer                                                    //
// ------------------------------------------------------------------------- //

sdl_immediate_renderer::sdl_immediate_renderer(SDL_Renderer* renderer)
    : m_transform_stack({mth::linear_transform2(mth::IDENTITY_INITIALIZATION)})
    , m_renderer(renderer) {}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::push_transform(const mth::linear_transform2 &transform) {
    m_transform_stack.push_back(transform * peek_transform());
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::pop_transform() {
    assert(m_transform_stack.size() > 1 && "unable to pop transform from empty stack!");
    if (m_transform_stack.size() > 1) {
        m_transform_stack.pop_back();
    }
}

// ------------------------------------------------------------------------- //

inline const mth::linear_transform2 &sdl_immediate_renderer::peek_transform() const {
    return m_transform_stack.back();
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_color(const mth::color &c) {
    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_point(const mth::point2 &point) {
    const mth::linear_transform2 &transform = peek_transform();

    const mth::point2 a = transform * point;
    SDL_Rect rect = { int(a.x) - 2, int(a.y) - 2, 4, 4 };
    SDL_RenderDrawRect(m_renderer, &rect);
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_point(const std::vector<mth::point2> &points) {
    for (const mth::point2 &point : points) {
        draw_point(point);
    }
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_line(const mth::line2 &line) {
    const mth::linear_transform2 &transform = peek_transform();

    const mth::line2::pointset_type &points = line.points();
    for (int i = 1, e = points.size(); i < e; ++i) {
        const mth::point2 a = transform * points[i - 1];
        const mth::point2 b = transform * points[i];

        SDL_RenderDrawLine(m_renderer, int(a.x), int(a.y), int(b.x), int(b.y));
    }
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_line(const std::vector<mth::line2> &lines) {
    for (const mth::line2 &line: lines) {
        draw_line(line);
    }
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_polygon(const mth::polygon2 &polygon) {
    const mth::linear_transform2 &transform = peek_transform();

    const mth::polygon2::pointset_type &points = polygon.points();
    for (int i = 0, e = points.size(); i < e; ++i) {
        const mth::point2 &a = transform * points[i];
        const mth::point2 &b = transform * points[(i + 1) % e];

        SDL_RenderDrawLine(m_renderer, int(a.x), int(a.y), int(b.x), int(b.y));
    }
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::draw_polygon(const std::vector<mth::polygon2> &polygons) {
    for (const mth::polygon2 &polygon : polygons) {
        draw_polygon(polygon);
    }
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::fill_point(const mth::point2 &point) {
    const mth::linear_transform2 &transform = peek_transform();

    const mth::point2 a = transform * point;
    SDL_Rect rect = { int(a.x) - 2, int(a.y) - 2, 4, 4 };
    SDL_RenderFillRect(m_renderer, &rect);
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::fill_point(const std::vector<mth::point2> &points) {
    for (const mth::point2 &point : points) {
        fill_point(point);
    }
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::clear() {
    SDL_RenderClear(m_renderer);
}

// ------------------------------------------------------------------------- //

inline void sdl_immediate_renderer::present() {
    SDL_RenderPresent(m_renderer);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
