// header include
#include "sdl_system_event_pump.h"

// sdl includes
#include <SDL.h>

// gea includes
#include <gea\demo\core\event\system_event.h>

namespace gea {

namespace {

// ------------------------------------------------------------------------- //

const bool convert_native_window_event(const SDL_WindowEvent &window_event, system_event &event) {
    switch (window_event.event)
    {
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        event.type = system_event_type__window_focus;
        event.window_focus.has_focus = true;
        return true;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        event.type = system_event_type__window_focus;
        event.window_focus.has_focus = false;
        return true;
    }

    return false;
}

const bool convert_native_keyboard_event(const SDL_KeyboardEvent &keyboard_event, system_event &event) {
    const SDL_Keysym &keysym = keyboard_event.keysym;
    if (keyboard_event.repeat != 0) {
        event.type = system_event_type__key_repeat;
        event.key_input = { uint32_t(keysym.sym), uint32_t(keysym.scancode), uint16_t(keysym.mod) };
        return true;
    } else if (keyboard_event.type == SDL_KEYUP) {
        event.type = system_event_type__key_up;
        event.key_input = { uint32_t(keysym.sym), uint32_t(keysym.scancode), uint16_t(keysym.mod) };
        return true;
    } else if (keyboard_event.type == SDL_KEYDOWN) {
        event.type = system_event_type__key_down;
        event.key_input = { uint32_t(keysym.sym), uint32_t(keysym.scancode), uint16_t(keysym.mod) };
        return true;
    }

    return false;
}

const bool convert_native_system_event(const SDL_Event &native_event, system_event &event) {
    switch (native_event.type)
    {
    case SDL_QUIT:
        event.type = system_event_type__window_quit;
        return true;
    case SDL_WINDOWEVENT:
        return convert_native_window_event(native_event.window, event);
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        return convert_native_keyboard_event(native_event.key, event);
    }

    return false;
}

} // namespace //

// ------------------------------------------------------------------------- //
// sdl_system_event_pump                                                     //
// ------------------------------------------------------------------------- //

sdl_system_event_pump::sdl_system_event_pump(system_event_listener *listener) : system_event_pump(listener) {}

// ------------------------------------------------------------------------- //

sdl_system_event_pump::~sdl_system_event_pump() {}

// ------------------------------------------------------------------------- //

const bool sdl_system_event_pump::poll() {
    SDL_Event native_event;
    const bool ret = (SDL_PollEvent(&native_event) != 0);

    system_event event;
    if (convert_native_system_event(native_event, event))
        dispatch(event);
    return ret;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
