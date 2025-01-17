#include <stdint.h>

#include "init.h"
#include "input.h"
#include "render.h"
#include "settings.h"

SDL_Window* glWindow = NULL;
SDL_GLContext* glContext = NULL;

int main() {
    if (init("OpenGL", WIDTH, HEIGHT)) {
        return 1;
    }

    vertexSpec();
    shaderSpec("shaders/vert.glsl", "shaders/frag.glsl");
    preDraw(true);

    getInfo();

    int8_t do_render = 1;

    while (1) {
        // Listen events
        if (listenEvents(SDL_SCANCODE_SPACE)) {
            do_render = !do_render;
        }
        if (do_render) {
            draw();
            // Update window
            SDL_GL_SwapWindow(glWindow);
        }
        SDL_Delay(16);
    }
    return 0;
}
