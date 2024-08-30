#include "sdl.h"
#include "input.h"
#include "render.h"


SDL_Window* window; 
SDL_Renderer* renderer; 
int pause = 0; 


int main() {
	
	if (initSDL("Hello SDL", WIDTH, HEIGHT)) {
		return 1; 
	} 
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	prepRender(); 
	
	
	while (1) {
		listenInput();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		if (!pause) {
			render(); 

			SDL_RenderPresent(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
		}
		SDL_Delay(16);
		
	}

}

