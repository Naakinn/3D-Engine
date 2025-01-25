#include "init.h"

#include "glad/glad.h"
#include "qlog.h"
#include "render_types.h"

#ifdef DEBUG
#include "error.h"
#endif

extern SDL_GLContext* glContext;
extern SDL_Window* glWindow;
extern VBO glVBOVertex;
extern GLuint glEBO;
extern GLuint glVAO;

int init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        QLOGF(qlERROR, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glWindow = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL);
    if (glWindow == NULL) {
        QLOGF(qlERROR, "SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }

    glContext = (SDL_GLContext*)SDL_GL_CreateContext(glWindow);
    if (glContext == NULL) {
        QLOGF(qlERROR, "SDL_GL_CreateContext: %s\n", SDL_GetError());
        return 1;
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        QLOGF(qlERROR, "Glad Load Error\n");
        return 1;
    }

#ifdef DEBUG
    QLOGF(qlDEBUG, "Running in debug mode\n");
    glCheckCall(glEnable(GL_DEBUG_OUTPUT));
    glDebugMessageCallback(messageCallback, 0);
#endif

    return 0;
}

void quit() {
    QLOGF(qlINFO, "Exiting\n");
    glDeleteBuffers(1, &glVBOVertex.name);
    glDeleteBuffers(1, &glEBO);
    glDeleteVertexArrays(1, &glVAO);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(glWindow);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}
