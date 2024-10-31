#include "init.h"
#include "input.h"

int is_running = 0; 

void handleKeyUp(SDL_KeyboardEvent* event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
			is_running = ~is_running; 
		}
	}
}

void listenInput() { 
	
	SDL_Event event; 
	
	while (SDL_PollEvent(&event)) { 
		switch (event.type) { 
			
			case SDL_QUIT: 
				quit(); 
				
			case SDL_KEYUP:
				handleKeyUp(&event.key);
				break; 
			default: 
				break; 
		}
	}
}

