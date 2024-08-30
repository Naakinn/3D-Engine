#include "sdl.h"

void listenInput() { 
	
	SDL_Event event; 
	
	while (SDL_PollEvent(&event)) { 
		switch (event.type) { 
			case SDL_QUIT: 
				quitSDL(); 
			default: 
				break; 
		}
	}
}
