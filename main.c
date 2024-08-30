#include "sdl.h"
#include "input.h"
#include "render.h"


SDL_Window* window; 
SDL_Renderer* renderer; 


// gcc -I include/ main.c sdl.c input.c `sdl2-config --cflags --libs`
int main() {
	
	if (initSDL("Hello SDL", WIDTH, HEIGHT)) {
		return 1; 
	} 
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	/* some runtime calculation */
	prepRender(); 
	render(); 
	
	SDL_RenderPresent(renderer);

	while (1) {
		listenInput();
		SDL_Delay(16);
	}

}

