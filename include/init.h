#ifndef __init_h_
#define __init_h_

#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif 

#ifdef __cplusplus
extern "C" {
#endif

int init(const char* title, int width, int height);
void quit();

#ifdef __cplusplus
}
#endif

#endif
