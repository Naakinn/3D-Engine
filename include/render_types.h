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

#define setUniformName(u) u.name = #u
#define setUniformLocation(u) u.location = glGetUniformLocation(GLPIPELINEPROGRAM, u.name)

typedef struct {
    GLuint name;  
    GLuint vertIdx;  // Index of the generic vertex attribute for vertices(layout)
    GLuint colIdx;   // Index of the generic vertex attribute for color(layout)
} VBO;

typedef struct {
    GLint location;
    const char* name;
} Uniform;

#endif
