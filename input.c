#include "sdl.h"

extern int pause; 

void listenInput() { 
	
	SDL_Event event; 
	
	while (SDL_PollEvent(&event)) { 
		switch (event.type) { 
			case SDL_QUIT: 
				quitSDL(); 
			/* TODO */
			case SDLK_SPACE:
				pause = ~pause; 
				printf("paused\n"); 
				break; 
			default: 
				break; 
		}
	}
}
