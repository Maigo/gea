// header include 
#include "application.h"

// std includes
#include <stdio.h>

// sdl includes
#include <SDL.h>

// gea includes
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
    m_window = SDL_CreateWindow("demo: sdl_sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
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

    // add stuff here

    // swap buffers
    renderer.present();
}

// ------------------------------------------------------------------------- //

} // namespace gea //
