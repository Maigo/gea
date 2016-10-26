// header include 
#include "application.h"

// std includes
#include <stdio.h>

// sdl includes
#include <SDL.h>

// gea includes
#include <gea\mth_vector\linear_transform2.h>
#include <gea\mth_graph\algorithm\point_reduce.h>
#include <gea\mth_graph\algorithm\sampler.h>

#include <gea/demo/sdl/render/sdl_immediate_renderer.h>

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

application::application() : super_t(), m_window(nullptr), m_renderer(nullptr) {}

// ------------------------------------------------------------------------- //

application::~application() {}

// ------------------------------------------------------------------------- //

void application::initialize() {
    super_t::initialize();

    // initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // create window
    m_window = SDL_CreateWindow("demo: sdl_point_reduce", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // get window renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    // sample line
    mth::sampler::sample(100.0f, 540.0f, 10.0f, [](const float x)->const float{ return 140.0f * sinf(x / 100.0f) + 240.0f; }, m_line);

    // reduce line
    mth::point_reduce::point_reduce(m_line, 5.0f, m_reducedLine);
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
    
    // fill buffer with white
    renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xFF, 0xFF, 0xFF));
    renderer.clear();

    // draw full line
    {
        mth::linear_transform2 move_up(mth::matrix2::IDENTITY, mth::vector2(0, -20));
        renderer.push_transform(move_up);

        // draw lines
        renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0x00, 0x00, 0xFF));
        renderer.draw_line(m_line);

        // draw points
        renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xFF, 0x0, 0x00));
        renderer.draw_point(m_line.points());

        renderer.pop_transform();
    }

    // draw reduced line
    {
        mth::linear_transform2 move_down(mth::matrix2::IDENTITY, mth::vector2(0, 20));
        renderer.push_transform(move_down);

        // draw lines
        renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0x00, 0x00, 0xFF));
        renderer.draw_line(m_reducedLine);

        // draw points
        renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xFF, 0x0, 0x00));
        renderer.draw_point(m_reducedLine.points());

        renderer.pop_transform();
    }

    // swap buffers
    renderer.present();
}

// ------------------------------------------------------------------------- //

} // namespace gea //
