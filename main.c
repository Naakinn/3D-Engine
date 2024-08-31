#include "sdl.h"
#include "input.h"
#include "render.h"

#define COLOR_STEP 1; 

SDL_Window* window; 
SDL_Renderer* renderer; 
int pause = 0; 


int main() {
	
	if (initSDL("Hello SDL", WIDTH, HEIGHT)) {
		return 1; 
	} 
	
	struct color cBlack = { 0, 0, 0, 255 }; 
	struct color cWhite = { 255, 255, 255, 255 }; 
	struct color temp = { 255, 0, 0, 255 };  

	setColor(cBlack); 
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	prepRender(); 
	
	while (1) {
		
		setColor(cBlack);
		SDL_RenderClear(renderer);
		
		listenInput();

		
		if (!pause) {
			if (temp.r == 255 && temp.g == 0 && temp.b != 255) {
				temp.b += COLOR_STEP; 
			} 
			else if (temp.b == 255 && temp.g == 0 && temp.r > 0) {
				temp.r -= COLOR_STEP; 
			} 
			else if (temp.b == 255 && temp.r == 0 && temp.g != 255) {
				temp.g += COLOR_STEP; 
			} 
			else if (temp.g == 255 && temp.r == 0 && temp.b > 0) {
				temp.b -= COLOR_STEP; 
			} 
			else if (temp.g == 255 && temp.b ==  0 && temp.r != 255) {
				temp.r += COLOR_STEP; 
			} 
			else if (temp.r == 255 && temp.b == 0) {
				temp.g -= COLOR_STEP; 
			}
			setColor(temp); 
			render(); 
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(16);
		
	}

}

