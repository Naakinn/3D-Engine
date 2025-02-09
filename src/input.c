#include "input.h"

#include "init.h"

int handleKeyUp(SDL_KeyboardEvent* event, SDL_Scancode scancode) {
    if (event->repeat == 0) {
        if (event->keysym.scancode == scancode) {
            return 1;
        }
    }
    return 0;
}

int listenEvents(SDL_Scancode scancode) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYUP:
                return handleKeyUp(&event.key, scancode);
                break;
            case SDL_QUIT:
                quit(EXIT_FAILURE);
            default:
                break;
        }
    }
    return 0;
}
