#include "init.h"
#include "input.h"
#include "render.hpp"

SDL_Window* window; 
SDL_Renderer* renderer; 
extern int is_running; 


int main() {
	
	if (init("Hello SDL", WIDTH, HEIGHT)) {
		return 1; 
	} 
	
	struct color cBlack = { 0, 0, 0, 255 }; 
	struct color cWhite = { 255, 255, 255, 255 }; 

	setColor(cBlack); 
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	preRender(); 
	
	while (1) {
		
		setColor(cBlack);
		SDL_RenderClear(renderer);
		
		listenInput();

		
		if (!is_running) {
			setColor(cWhite); 
			render(); 
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(16);
		
	}

}

