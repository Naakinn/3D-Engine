#include "render.hpp"

#include <glad/glad.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "init.h"
#include "qlog.h"
#include "render_types.h"
#include "settings.h"
#include "shader.h"

// VAO
GLuint glVAO = 0;
// VBO
VBO glVBOVertex = {0, 0, 1};
// EBO
GLuint glEBO = 0;
// Grapshics pipeline shader program
GLuint glPipeLineProgram = 0;
#define GLPIPELINEPROGRAM glPipeLineProgram

GLuint vertexNumber;
GLuint elementNumber;

// Perspective
const float aspect = (float)WIDTH / (float)HEIGHT;
const float absoluteScale =
    (float)SCALE_FACTOR / (float)(HEIGHT < WIDTH ? HEIGHT : WIDTH);
const float fov = 45.0f;

static Uniform uTranslation, uProjection, uRotation, uScale;
// static Uniform uTime;

void vertexSpec() {
    // clang-format off
    const GLfloat vertexData[] = {
         // 0
        -0.5f, -0.5f,  0.5f,  // Vertex position
         1.0f,  0.0f,  0.0f,  // Color
         // 1
         0.5f, -0.5f,  0.5f,
         0.0f,  1.0f,  0.0f,
         // 2
        -0.5f,  0.5f,  0.5f,
         0.0f,  0.0f,  1.0f,
         // 3
         0.5f,  0.5f,  0.5f,
         1.0f,  0.0f,  0.0f,
		 // 4
		 0.5f, -0.5f, -0.5f,
		 0.0f,  1.0f,  0.0f,
		 // 5
		 0.5f,  0.5f, -0.5f,
		 0.0f,  0.0f,  1.0f,
		 // 6
        -0.5f, -0.5f, -0.5f,  
         0.0f,  0.0f,  1.0f,  
         // 7
        -0.5f,  0.5f, -0.5f, 
         0.0f,  1.0f,  0.0f,
    };  // clang-format on
    const GLuint elementData[] = {1, 2, 0, 1, 3, 2, 4, 3, 1, 4, 5, 3,
                                  0, 7, 6, 0, 2, 7, 3, 7, 2, 3, 5, 7,
                                  4, 1, 0, 4, 0, 6, 6, 7, 5, 6, 5, 4};
    vertexNumber = sizeof(vertexData) / sizeof(GLfloat) / VERTEXSIZE;
    elementNumber = sizeof(elementData) / sizeof(GLuint);

    QLOGF(qlINFO, "Number of vertices: %u\n", vertexNumber);

    // Generate VAO
    glGenVertexArrays(1, &glVAO);
    // Select VAO
    glBindVertexArray(glVAO);
    // Generate VBO
    glGenBuffers(1, &glVBOVertex.name);
    // Select vertex VBO
    glBindBuffer(GL_ARRAY_BUFFER, glVBOVertex.name);

    // Fill vertex VBO with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);

    // EBO
    glGenBuffers(1, &glEBO);
    // Select EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEBO);
    // Fill EBO with data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData,
                 GL_STATIC_DRAW);

    // Set vertex attributes in VBO
    glEnableVertexAttribArray(glVBOVertex.vertIdx);
    glVertexAttribPointer(glVBOVertex.vertIdx, POSSIZE, GL_FLOAT, GL_FALSE,
                          VERTEXSIZE * sizeof(GLfloat), (GLvoid*)0);

    // Set color attributes in the same VBO
    glEnableVertexAttribArray(glVBOVertex.colIdx);
    glVertexAttribPointer(glVBOVertex.colIdx, COLORSIZE, GL_FLOAT, GL_FALSE,
                          VERTEXSIZE * sizeof(GLfloat),
                          (GLvoid*)(POSSIZE * sizeof(GLfloat)));
}
void shaderSpec(const char* vertex, const char* fragment) {
    // Load shaders
    glPipeLineProgram =
        createShaderProgram(loadShader(vertex), loadShader(fragment));
    glUseProgram(glPipeLineProgram);
}

void getInfo() {
    QLOGF(qlINFO, "Vendor: %s\n", glGetString(GL_VENDOR));
    QLOGF(qlINFO, "Renderer: %s\n", glGetString(GL_RENDERER));
    QLOGF(qlINFO, "Version: %s\n", glGetString(GL_VERSION));
    QLOGF(qlINFO, "Shading language: %s\n",
           glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int checkUniform(const Uniform* u) {
    if (u->location < 0) {
        QLOGF(qlERROR, "Couldn't find uniform `%s`, location: %d\n", u->name,
              u->location);
        quit();
    }
    return 0;
}

void preDraw(bool culling) {
    if (culling) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    setUniformName(uTranslation);
    setUniformName(uProjection);
    setUniformName(uRotation);
    setUniformName(uScale);
    // setUniformName(uTime);

    setUniformLocation(uTranslation);
    setUniformLocation(uProjection);
    setUniformLocation(uRotation);
    setUniformLocation(uScale);
    // setUniformLocation(uTime);

    if (checkUniform(&uTranslation) != 0) quit();
    if (checkUniform(&uProjection) != 0) quit();
    if (checkUniform(&uRotation) != 0) quit();
    if (checkUniform(&uScale) != 0) quit();
    // if (checkUniform(&uTime) != 0) quit();
}

void draw() {
    static float rotationAngleX = 0.0f;
    static float rotationAngleY = 0.0f;
    static float zOffset = 0.0f;
    // float time;

    // Listen input
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W]) {
        zOffset -= 0.01f;
    }
    if (state[SDL_SCANCODE_S]) {
        zOffset += 0.01f;
    }

    rotationAngleX += 1.0f;
    rotationAngleY += 1.0f;

    // Build matrices
    glm::mat4 translate =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zOffset - 3.0f));
    glm::mat4 projection =
        glm::perspective(glm::radians(fov), aspect, NEAR, FAR);
    // glm::ortho(1.0f, -1.0f, 1.0f, -1.0f, FAR, NEAR);

    glm::mat4 rotationY =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationX =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX),
                    glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(absoluteScale));

    glm::mat4 rotation = rotationY * rotationX;

    // Set uniforms
    glUniformMatrix4fv(uRotation.location, 1, GL_FALSE, &rotation[0][0]);
    glUniformMatrix4fv(uTranslation.location, 1, GL_FALSE, &translate[0][0]);
    glUniformMatrix4fv(uProjection.location, 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(uScale.location, 1, GL_FALSE, &scale[0][0]);

    // Update uTime uniform
    // time = SDL_GetTicks() / 1000.0f;
    // glUniform1f(uTime.location, time);

    // Draw
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, elementNumber, GL_UNSIGNED_INT, 0);
}
