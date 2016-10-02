
// header include 
#include "application.h"

// std includes
#include <stdio.h>

// sdl includes
#include <SDL.h>

// gea includes
#include <gea\mth_graph\algorithm\sampler.h>

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

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Create window
    m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Get window renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    // sample line
    mth::sampler::sample(100.0f, 540.0f, 10.0f, [](const float x)->const float{ return 140.0f * sinf(x / 100.0f) + 240.0f; }, m_line);
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

    // Quit SDL subsystems
    SDL_Quit();

    super_t::deinitialize();
};

// ------------------------------------------------------------------------- //

static void drawLine(SDL_Renderer* renderer, const mth::line2 &line) {
    const mth::line2::points_type &points = line.points();
    for (int i = 1, e = points.size(); i < e; ++i) {
        const mth::point2 &a = points[i - 1];
        const mth::point2 &b = points[i];

        SDL_RenderDrawLine(renderer, int(a.x), int(a.y), int(b.x), int(b.y));
    }
}

// ------------------------------------------------------------------------- //

static void drawPoints(SDL_Renderer* renderer, const mth::line2 &line) {
    const mth::line2::points_type &points = line.points();
    for (int i = 0, e = points.size(); i < e; ++i) {
        const mth::point2 &a = points[i];

        SDL_Rect rect = { int(a.x) - 2, int(a.y) - 2, 4, 4 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// ------------------------------------------------------------------------- //

void application::render(const render_context &context) {
    // Fill buffer with white
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);

    // Draw lines
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);

    drawLine(m_renderer, m_line);

    // Draw points
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);

    drawPoints(m_renderer, m_line);

    // Swap buffers
    SDL_RenderPresent(m_renderer);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
