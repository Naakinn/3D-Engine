#ifndef __render_private_h
#define __render_private_h

#include <stdbool.h>

#include "glad/glad.h"

#define VERTEXSIZE 6
#define POSSIZE 3
#define COLORSIZE 3

#define FAR 10.0f
#define NEAR 0.1f

#define setUniformName(u) u.name = #u
#define setUniformLocation(u) \
    u.location = glGetUniformLocation(GLPIPELINEPROGRAM, u.name)

typedef struct {
    bool enabled;
    GLuint name;
    GLuint
        vertIdx;  // Index of the generic vertex attribute for vertices(layout)
    GLuint colIdx;  // Index of the generic vertex attribute for color(layout)
} glVBO_t;

typedef struct {
    bool enabled;
    GLuint name;
} glBaseGLuint_t;

typedef glBaseGLuint_t glEBO_t;
typedef glBaseGLuint_t glVAO_t;

typedef struct {
    GLint location;
    const char* name;
} glUniform_t;

#endif
