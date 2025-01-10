#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "init.h"

char* loadShader(const char* filepath) {
    FILE* istream = fopen(filepath, "r");

    if (istream == NULL) {
        fprintf(stderr, "[ERROR] Couldn't open file %s\n", filepath);
        quit(); 
    }

    size_t size;
    char c;
    int i;

    for (size = 0; (c = fgetc(istream)) != EOF; ++size);
    char* shaderSource = (char*)malloc(size * sizeof(char) + 1);

    if (shaderSource == NULL) {
        fprintf(stderr, "[ERROR] Allocation error, size: %lu bytes, at line %d",
               size * sizeof(char), __LINE__);
        quit();
    }

    rewind(istream);
    for (i = 0; (c = fgetc(istream)) != EOF; ++i) {
        shaderSource[i] = c;
    }

    shaderSource[i] = '\0';

    fclose(istream);
    return shaderSource;
}

GLuint compileShader(GLuint type, const char* source) {
    GLuint shaderObject;
    switch (type) {
        case GL_VERTEX_SHADER:
            shaderObject = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GL_FRAGMENT_SHADER:
            shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    glShaderSource(shaderObject, 1, &source, 0);
    glCompileShader(shaderObject);
    free((void*)source);
    return shaderObject;
}

GLuint createShaderProgram(const char* vertexShaderSource,
                           const char* fragmentShaderSource) {
    GLuint programObject = glCreateProgram();
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);

    /* Clean up */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}
