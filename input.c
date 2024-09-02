#include "init.h"

extern int pause; 

void handleKeyUp(SDL_KeyboardEvent* event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
			pause = ~pause; 
		}
	}
}

void listenInput() { 
	
	SDL_Event event; 
	
	while (SDL_PollEvent(&event)) { 
		switch (event.type) { 
			
			case SDL_QUIT: 
				quitSDL(); 
				
			case SDL_KEYUP:
				handleKeyUp(&event.key);
				break; 
			default: 
				break; 
		}
	}
}

