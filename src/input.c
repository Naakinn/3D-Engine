#include "input.h"
#include "init.h"

void checkQuit() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
				quit(); 
				break; 
            default:
                break;
        }
	}
}
