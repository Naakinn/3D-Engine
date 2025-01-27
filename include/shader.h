#ifndef __shader_h_
#define __shader_h_

#include "glad/glad.h"

GLuint compileShader(GLuint type, const char* source);

GLuint createShaderProgram(const char* vertexSrc, const char* fragmentSrc);

#endif
