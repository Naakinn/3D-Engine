#ifndef __render_private_h
#define __render_private_h

#ifndef __glad_h_
#include "glad/glad.h"
#endif

#define VERTEXSIZE 6
#define POSSIZE 3
#define COLORSIZE 3

#define FAR 10.0f
#define NEAR 0.1f

typedef struct VBOVertex {
    GLuint name;     // VBO name
    GLuint vertIdx;  // Index of the generic vertex attribute for vertices
    GLuint colIdx;   // Index of the generic vertex attribute for color
} glVBOVertex_t;

typedef struct glUniformMatrix {
    GLint location;
    const char* name;
} glUniformMatrix_t;

#endif
