#ifndef __GEA_DEMO_SDL_IMMEDIATE_RENDERER_H__
#define __GEA_DEMO_SDL_IMMEDIATE_RENDERER_H__

// std includes
#include <vector>

// sdl includes
#include <SDL.h>

// gea includes
#include <gea/mth_geometry/line2.h>
#include <gea/mth_geometry/polygon2.h>
#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/linear_transform2.h>
#include <gea/mth_visual/color.h>

namespace gea {

// ------------------------------------------------------------------------- //
// sdl_immediate_renderer                                                    //
// ------------------------------------------------------------------------- //

class sdl_immediate_renderer {
public:
    sdl_immediate_renderer(SDL_Renderer* renderer);

    void push_transform(const mth::linear_transform2 &transform);
    void pop_transform();
    const mth::linear_transform2 &peek_transform() const;

    void draw_color(const mth::color &c);

    void draw_point(const mth::point2 &point);
    void draw_point(const std::vector<mth::point2> &points);
    void draw_line(const mth::line2 &line);
    void draw_line(const std::vector<mth::line2> &lines);
    void draw_polygon(const mth::polygon2 &polygon);
    void draw_polygon(const std::vector<mth::polygon2> &polygons);

    void clear();

    void present();

private:
    typedef std::vector<mth::linear_transform2> transform_stack;
    transform_stack         m_transform_stack;

    SDL_Renderer            *m_renderer;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "sdl_immediate_renderer.inl"

#endif // __GEA_DEMO_SDL_IMMEDIATE_RENDERER_H__ //
