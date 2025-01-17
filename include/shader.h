#ifndef __shader_h_
#define __shader_h_

#ifndef __glad_h_
#include "glad/glad.h"
#endif

char* loadShader(const char* filepath);

GLuint compileShader(GLuint type, const char* source);

GLuint createShaderProgram(const char* vertexShaderSource,
                           const char* fragmentShaderSource);

#endif

