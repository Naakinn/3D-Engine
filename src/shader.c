#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "qlog.h"

GLuint compileShader(GLuint type, const char* source) {
    GLuint shaderObject = -1;
    switch (type) {
        case GL_VERTEX_SHADER:
            shaderObject = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GL_FRAGMENT_SHADER:
            shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            QLOGF(qlERROR, "Couldn't recognise shader type %d\n", type);
            return shaderObject;
            break;
    }
    glShaderSource(shaderObject, 1, &source, NULL);
    glCompileShader(shaderObject);
    QLOGF(qlDEBUG, "Compiled shader object %u\n", shaderObject);
    return shaderObject;
}

GLuint createShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
    GLuint programObject = glCreateProgram();
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);
    QLOGF(qlDEBUG, "Created program shader object %u\n", programObject);

    /* Clean up */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}
