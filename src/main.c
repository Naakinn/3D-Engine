#include <getopt.h>
#include <stdint.h>

#include "common.h"
#include "init.h"
#include "input.h"
#include "qlog.h"
#include "render.h"
#include "settings.h"

static char* short_options =
    "ht:";  // ':' after a flag means that it requires argument.
static struct option long_options[] = {{"texture", required_argument, 0, 't'},
                                       {0, 0, 0, 0}};
static const char* texturePath = NULL;

SDL_Window* glWindow = NULL;
SDL_GLContext* glContext = NULL;

void usage() {
    printf("Usage: ./engine [OPTION]...\n");
    printf("Basic 3D engine, idk what to implement. \n");
    printf("\t-t --texture <FILE> Draw textures from FILE.\n");
    printf("\t-h --help Display help page.\n");
}

int parse_arg(int argc, char* argv[]) {
    int result = 0, c;

    while (true) {
        c = getopt_long(argc, argv, short_options, long_options, NULL);

        if (c == -1) return_defer(-1);

        switch (c) {
            case 'h':
                return_defer(EXIT_HELP);
            case 't':
                texturePath = optarg;
                break;
            default:
                QLOGF(qlERROR,
                      "getopt returned character code "
                      "0x%x\n",
                      c);
                return_defer(EXIT_FAILURE);
        }
    }

defer:
    return result;
}

int main(int argc, char* argv[]) {
    int result = EXIT_SUCCESS;
    int parse_status = parse_arg(argc, argv);

    switch (parse_status) {
        case EXIT_HELP:
            usage();
            return_defer(EXIT_SUCCESS);
        case EXIT_FAILURE:
            QLOGF(qlERROR, "Failure parsing command line arguments\n");
            return_defer(EXIT_FAILURE);
    }

    if (texturePath) QLOGF(qlDEBUG, "Path to texture: %s\n", texturePath);

    if (init("OpenGL", WIDTH, HEIGHT)) {
        return 1;
    }

    getInfo();

    vertexSpec();
    shaderSpec("shaders/vert.glsl", "shaders/frag.glsl");
    preDraw(true);

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
defer:
	quit(result); 
}
