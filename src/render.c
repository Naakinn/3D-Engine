#include "render.h"

#include <cglm/cglm.h>
#include <glad/glad.h>
#include <stdio.h>

#include "common.h"
#include "init.h"
#include "qlog.h"
#include "render_types.h"
#include "settings.h"
#include "shader.h"

glVAO_t glVAO = { .name = 0 };
glVBO_t glVBOVertex = {.name = 0, .vertIdx = 0, .colIdx = 1};
glEBO_t glEBO = { .name = 0 };

// Grapshics pipeline shader program
GLuint glPipeLineProgram = 0;
#define GLPIPELINEPROGRAM glPipeLineProgram

GLuint vertexNumber;
GLuint elementNumber;

// Perspective
static const float aspect = (float)WIDTH / (float)HEIGHT;
static const float fov = 45.0f;

// Matrices and uniforms
static glUniform_t uTranslation, uProjection, uRotation;
static mat4 translate, projection, rotationY, rotationX, rotation;

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
	glVAO.enabled = true;
    glGenVertexArrays(1, &glVAO.name);
    // Select VAO
    glBindVertexArray(glVAO.name);
    // Generate VBO
	glVBOVertex.enabled = true;
    glGenBuffers(1, &glVBOVertex.name);
    // Select vertex VBO
    glBindBuffer(GL_ARRAY_BUFFER, glVBOVertex.name);

    // Fill vertex VBO with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);

    // EBO
	glEBO.enabled = true;
    glGenBuffers(1, &glEBO.name);
    // Select EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEBO.name);
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
    int8_t result = 0;
    char *vertexSrc = NULL, *fragmentSrc = NULL;

    vertexSrc = readFile(vertex);
    if (vertexSrc == NULL) return_defer(-1);
    fragmentSrc = readFile(fragment);
    if (fragmentSrc == NULL) return_defer(-1);

    glPipeLineProgram = createShaderProgram(vertexSrc, fragmentSrc);
    glUseProgram(glPipeLineProgram);

defer:
    if (result)
        QLOGF(qlERROR, "Couldn't read shader file(s) %s, %s\n", vertex,
              fragment);
    if (vertexSrc) free(vertexSrc);
    if (fragmentSrc) free(fragmentSrc);
}

void getInfo() {
    QLOGF(qlINFO, "Vendor: %s\n", glGetString(GL_VENDOR));
    QLOGF(qlINFO, "Renderer: %s\n", glGetString(GL_RENDERER));
    QLOGF(qlINFO, "Version: %s\n", glGetString(GL_VERSION));
    QLOGF(qlINFO, "Shading language: %s\n",
          glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int checkUniform(const glUniform_t* u) {
    if (u->location < 0) {
        QLOGF(qlERROR, "Couldn't find uniform `%s`, location: %d\n", u->name,
              u->location);
        return 1;
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

    setUniformLocation(uTranslation);
    setUniformLocation(uProjection);
    setUniformLocation(uRotation);

    if (checkUniform(&uTranslation)) quit(EXIT_FAILURE);
    if (checkUniform(&uProjection)) quit(EXIT_FAILURE);
    if (checkUniform(&uRotation)) quit(EXIT_FAILURE);
}

void draw() {
    static float rotationAngleX = 0.0f;
    static float rotationAngleY = 0.0f;
    static float zOffset = 0.0f;

    // Listen input
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_Q]) {
        quit(EXIT_SUCCESS);
    }
    if (state[SDL_SCANCODE_W]) {
        zOffset -= 0.01f;
    }
    if (state[SDL_SCANCODE_S]) {
        zOffset += 0.01f;
    }

    rotationAngleX += 1.0f;
    rotationAngleY += 1.0f;

    glm_translate_make(translate, (vec3){0.0f, 0.0f, zOffset - 3.0f});
    glm_perspective(glm_rad(fov), aspect, NEAR, FAR, projection);
    glm_rotate_make(rotationY, glm_rad(rotationAngleY),
                    (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate_make(rotationX, glm_rad(rotationAngleX),
                    (vec3){1.0f, 0.0f, 0.0f});
    glm_mul(rotationY, rotationX, rotation);

    // Set uniforms
    glUniformMatrix4fv(uRotation.location, 1, GL_FALSE,
                       (const GLfloat*)rotation);
    glUniformMatrix4fv(uTranslation.location, 1, GL_FALSE,
                       (const GLfloat*)translate);
    glUniformMatrix4fv(uProjection.location, 1, GL_FALSE,
                       (const GLfloat*)projection);

    // Draw
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, elementNumber, GL_UNSIGNED_INT, 0);
}
