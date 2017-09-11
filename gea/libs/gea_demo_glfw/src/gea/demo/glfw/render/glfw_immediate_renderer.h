#ifndef __GEA_DEMO_GLFW_IMMEDIATE_RENDERER_H__
#define __GEA_DEMO_GLFW_IMMEDIATE_RENDERER_H__

// std includes
#include <vector>

// glfw includes
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <GLFW/glfw3.h>

// gea includes
#include <gea/mth_geometry/line2.h>
#include <gea/mth_geometry/rectangle2.h>
#include <gea/mth_geometry/polygon2.h>
#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/linear_transform2.h>
#include <gea/mth_visual/color.h>

#include <gea/demo/glfw/render/render_primitives.h>
#include <gea/demo/glfw/render/render_queue.h>

namespace gea {

// ------------------------------------------------------------------------- //
// glfw_immediate_renderer                                                   //
// ------------------------------------------------------------------------- //

class glfw_immediate_renderer {
public:
    glfw_immediate_renderer(/*SDL_Renderer* renderer*/);

    inline void push_transform(const mth::linear_transform2 &transform);
    inline void pop_transform();
    inline const mth::linear_transform2 &peek_transform() const;

    inline void draw_color(const mth::color &c);

    inline void draw_point(const mth::point2 &point);
    inline void draw_point(const std::vector<mth::point2> &points);
    inline void draw_line(const mth::line2 &line);
    inline void draw_line(const std::vector<mth::line2> &lines);
    inline void draw_rectangle(const mth::rectangle2 &rectangle);
    inline void draw_rectangle(const std::vector<mth::rectangle2> &rectangles);
    inline void draw_polygon(const mth::polygon2 &polygon);
    inline void draw_polygon(const std::vector<mth::polygon2> &polygons);

    inline void fill_point(const mth::point2 &point);
    inline void fill_point(const std::vector<mth::point2> &points);
    inline void fill_rectangle(const mth::rectangle2 &rectangle);
    inline void fill_rectangle(const std::vector<mth::rectangle2> &rectangles);

    inline void clear();

    inline void flush();

private:
    mth::color m_color;

    std::vector<render_queue_op> m_render_ops;
    std::vector<ren::vertex2_color> m_vertices;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "glfw_immediate_renderer.inl"

#endif // __GEA_DEMO_GLFW_IMMEDIATE_RENDERER_H__ //
