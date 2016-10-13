
// header include 
#include "application.h"

// std includes
#include <stdio.h>

// sdl includes
#include <SDL.h>

// gea includes
#include <gea/mth_geometry/rectangle2.h>
#include <gea/mth_vector/random2.h>

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

application::application() : super_t(), m_window(nullptr), m_renderer(nullptr) {}

// ------------------------------------------------------------------------- //

application::~application() {}

// ------------------------------------------------------------------------- //

static void random_points(const mth::point2 &nw_corner, const mth::point2 &se_corner, const uint32_t count, mth::polygon2::points_type &out_points) {
    for (int i = 0, e = count; i < e; ++i) {
        const mth::point2 point = mth::rand_point2(nw_corner, se_corner);
        out_points.push_back(point);
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

static void drawPolygon(SDL_Renderer* renderer, const mth::polygon2 &polygon) {
    const mth::polygon2::points_type &points = polygon.points();
    for (int i = 0, e = points.size(); i < e; ++i) {
        const mth::point2 &a = points[i];
        const mth::point2 &b = points[(i + 1) % e];

        SDL_RenderDrawLine(renderer, int(a.x), int(a.y), int(b.x), int(b.y));
    }
}

// ------------------------------------------------------------------------- //

static void drawPoints(SDL_Renderer* renderer, const mth::polygon2::points_type &points) {
    for (int i = 0, e = points.size(); i < e; ++i) {
        const mth::point2 &a = points[i];

        SDL_Rect rect = { int(a.x) - 2, int(a.y) - 2, 4, 4 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// ------------------------------------------------------------------------- //

void application::render(const render_context &context) {
    // fill buffer with white
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);

    // draw convex hull
    {
        // draw lines
        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
        drawPolygon(m_renderer, m_polygon);

        // draw points
        SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        drawPoints(m_renderer, m_points);
    }

    // swap buffers
    SDL_RenderPresent(m_renderer);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
