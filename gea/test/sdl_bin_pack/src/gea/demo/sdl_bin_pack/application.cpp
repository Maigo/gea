// header include
#include "application.h"

// std includes
#include <stdio.h>

// sdl includes
#include <SDL.h>

// gea includes
#include <gea/random/random.h>

#include <gea/demo/sdl/render/sdl_immediate_renderer.h>

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //

application::application() : super_t(), m_bin_pack({ 20, 20, SCREEN_WIDTH - 40, SCREEN_HEIGHT - 40 }), m_window(nullptr), m_renderer(nullptr) {}

// ------------------------------------------------------------------------- //

application::~application() {}

// ------------------------------------------------------------------------- //

static mth::rectangle2 random_rect(const float width, const float height) {
    const float r0 = g_random.rfloat(), r1 = g_random.rfloat();
    return { 0.0f, 0.0f, mth::round((0.1f * width) + (r0 * width * 0.9f)), mth::round((0.1f * height) + (r1 * height *0.9f)) };
}

// ------------------------------------------------------------------------- //

void application::initialize(const init_info& info) {
    super_t::initialize(info);

    // initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // create window
    m_window = SDL_CreateWindow("demo: sdl_bin_pack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // get window renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    // pack some rects
    bool generate = true;
    do {
        mth::rectangle2 rect = random_rect(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5);
        if (generate = m_bin_pack.bin_pack(rect))
            m_rects.push_back(rect);
    } while (generate);
}

// ------------------------------------------------------------------------- //

void application::deinitialize(const deinit_info& info) {
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

    super_t::deinitialize(info);
};

// ------------------------------------------------------------------------- //

void application::render(const render_context &context) {
    sdl_immediate_renderer renderer(m_renderer);

    // fill buffer with white
    renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xFF, 0xFF, 0xFF));
    renderer.clear();

    // draw unused space
    {
        mth::linear_transform2 move_down(mth::matrix2::IDENTITY, mth::vector2(0, 20));
        renderer.push_transform(move_down);

        // draw lines
        for (const mth::rectangle2& rect : m_bin_pack.stack()) {
            renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xFF, 0xCC, 0xCC));
            renderer.fill_rectangle(rect);
            renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xFF, 0x00, 0x00));
            renderer.draw_rectangle(rect);
        }

        renderer.pop_transform();
    }

    // draw packed rectangles
    {
        mth::linear_transform2 move_up(mth::matrix2::IDENTITY, mth::vector2(0, -20));
        renderer.push_transform(move_up);

        // draw rects
        for (const mth::rectangle2& rect : m_rects) {
            renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0xCC, 0xCC, 0xFF));
            renderer.fill_rectangle(rect);
            renderer.draw_color(mth::color(SDL_ALPHA_OPAQUE, 0x00, 0x00, 0xFF));
            renderer.draw_rectangle(rect);
        }

        renderer.pop_transform();
    }

    // swap buffers
    renderer.present();
}

// ------------------------------------------------------------------------- //

} // namespace gea //
