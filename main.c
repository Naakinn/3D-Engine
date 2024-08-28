#include <SDL2/SDL.h>
#include "graphics.h"

int initSDL(char* title, int width, int height); 
void quitSDL(); 

static SDL_Window* window; 
static SDL_Renderer* renderer; 

// gcc main.c graphics.c `sdl2-config --cflags --libs`
int main() {
	
	if (initSDL("Hello SDL", WINDOW_WIDTH, WINDOW_HEIGHT) != 0) {
		return 1; 
	} 
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	SDL_RenderDrawLine(renderer, scaleX(0), scaleY(0), scaleX(100), scaleY(100)); 

	SDL_RenderPresent(renderer);
	
	SDL_Delay(5000); 
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
