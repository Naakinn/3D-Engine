#ifndef __input_h_
#define __input_h_

#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif

int listenEvents(SDL_Scancode scancode);
void checkQuit(); 

#endif
