#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

int init(const char* title, int width, int height); 
void quit(); 

#ifdef __cplusplus
}
#endif

#endif
