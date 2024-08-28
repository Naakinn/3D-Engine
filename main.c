#include <SDL2/SDL.h>

int initSDL(char* title, int width, int height); 
void quitSDL(); 

static SDL_Window* window = 0; 
static SDL_Renderer* renderer = 0; 

// gcc main.c `sdl2-config --cflags --libs`
int main() {
	
	/* SDL basic initialization */
	if (initSDL("Hello SDL", 640, 480) != 0) {
		return 1; 
	} 
	
	/* Some SDL options */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	
	SDL_Delay(2000); 
	quitSDL();

	return 0;
}

int initSDL(char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return 1;
	}
	return 0; 
}

void quitSDL() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
