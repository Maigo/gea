// header include 
#include "application.h"

// std includes
#include <stdio.h>

// sdl includes
#include <SDL.h>

// gea includes
#include <gea/mth_geometry/rectangle2.h>
#include <gea/mth_graph/algorithm/convex_hull.h>
#include <gea/mth_vector/random2.h>

#include <gea/demo/sdl/render/sdl_immediate_renderer.h>

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

application::application() : super_t(), m_window(nullptr), m_renderer(nullptr) {}

// ------------------------------------------------------------------------- //

application::~application() {}

// ------------------------------------------------------------------------- //

static void random_points(const mth::point2 &nw_corner, const mth::point2 &se_corner, const uint32_t count, mth::polygon2::pointset_type &out_points) {
    for (int i = 0, e = count; i < e; ++i) {
        const mth::point2 point = mth::rand_point2(nw_corner, se_corner);
        out_points.push_back(mth::round(point));
    }
}

// ------------------------------------------------------------------------- //

void application::initialize() {
    super_t::initialize();

    // initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // create window
    m_window = SDL_CreateWindow("demo: sdl_simple", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // get window renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    // generate random points
    m_points.reserve(32);
    mth::rectangle2 area(mth::point2(20, 20), mth::vector2(SCREEN_WIDTH - 40, SCREEN_HEIGHT - 40));
    random_points(area.nw_corner(), area.se_corner(), 32, m_points);

    // calculate convex hull
    mth::convex_hull::convex_hull(m_points, m_polygon);
}

// ------------------------------------------------------------------------- //

void application::deinitialize() {
    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    
    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    // quit sdl subsystems
    SDL_Quit();

    super_t::deinitialize();
};

// ------------------------------------------------------------------------- //

void application::render(const render_context &context) {
    sdl_immediate_renderer renderer(m_renderer);

    static const mth::color color_white(SDL_ALPHA_OPAQUE, 0xFF, 0xFF, 0xFF);
    static const mth::color color_red(SDL_ALPHA_OPAQUE, 0xFF, 0x00, 0x00);
    static const mth::color color_blue(SDL_ALPHA_OPAQUE, 0x00, 0x00, 0xFF);

    // fill buffer with white
    renderer.draw_color(color_white);
    renderer.clear();

    // draw point set
    {
        // draw points
        renderer.draw_color(color_red);
        renderer.fill_point(m_points);
    }

    // draw convex hull
    {
        // draw lines
        renderer.draw_color(color_blue);
        renderer.draw_polygon(m_polygon);

        // draw points
        renderer.draw_color(color_blue);
        renderer.fill_point(m_polygon.points());
    }

    // swap buffers
    renderer.present();
}

// ------------------------------------------------------------------------- //

} // namespace gea //
