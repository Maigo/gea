#ifndef __GEA_DEMO_SDL_IMMEDIATE_RENDERER_H__
#define __GEA_DEMO_SDL_IMMEDIATE_RENDERER_H__

// std includes
#include <vector>

// sdl includes
#include <SDL.h>
//#include <SDL_ttf.h>

// gea includes
#include <gea/mth_geometry/line2.h>
#include <gea/mth_geometry/rectangle2.h>
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

    inline void present();

private:
    typedef std::vector<mth::linear_transform2> transform_stack;
    transform_stack         m_transform_stack;

    SDL_Renderer            *m_renderer;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "sdl_immediate_renderer.inl"

#endif // __GEA_DEMO_SDL_IMMEDIATE_RENDERER_H__ //
