#include "render.h"
#include "init.h"

#define ANGLE_STEP 0.015f
#define ZDISTANCE 2.5f

extern SDL_Renderer *renderer;

struct vec3 {
  float x, y, z;
};

struct triangle {
  struct vec3 v[3];
};

struct mesh {
  struct triangle *triangles;
} meshCube;

void multiplyVecMtx(struct vec3 *vec, float matrix[4][4]);
void drawTriangle(struct triangle *trg);

static const struct vec3 camera = { 0.0f, 0.0f, 0.0f };
static const float distNear = 1.0f;
static const float distFar = 1000.0f;
static const float screenAspectRatio = HEIGHT / WIDTH;
static const float fov = 90.0f;
static unsigned int trgc = 0;
static float fovRad;
static float rotAngleX = 0.0f;
static float rotAngleY = 0.0f;
static float rotAngleZ = 0.0f;

float matProjection[4][4] = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, distFar / (distFar - distNear), 1.0f },
    { 0.0f, 0.0f, -distFar *distNear / (distFar - distNear), 0.0f },
};
float mtxRotationX[4][4];
float mtxRotationY[4][4];
float mtxRotationZ[4][4];


void setColor(struct color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void preRender() {

  /* Calculations in runtime, but not in main loop */
  fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.141592f );
  matProjection[0][0] = screenAspectRatio * fovRad;
  matProjection[1][1] = fovRad;

  mtxRotationX[0][0] = 1.0f;
  mtxRotationX[3][3] = 1.0f;

  mtxRotationY[1][1] = 1.0f;
  mtxRotationY[3][3] = 1.0f;

  mtxRotationZ[2][2] = 1.0f;
  mtxRotationZ[3][3] = 1.0f;

  /* Some data */
  enum { size = 36 };
  struct vec3 vectors[size] = {
      0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

      1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0,
      1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

      1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

      1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  };
  trgc = size / 3;
  meshCube.triangles =
      (struct triangle *)malloc(sizeof(struct triangle) * trgc);

  int k = 0;
  for (int i = 0; i < trgc; ++i) {
    for (int j = 0; j < 3; ++j) {
      meshCube.triangles[i].v[j] = vectors[k];
      ++k;
    }
  }
}

void render() {

  struct triangle triangle;
  struct vec3 normal, line1, line2;
  float normalLength;

  /* Runtime calculations during render */
  rotAngleX += ANGLE_STEP * 1.5f;
  rotAngleY += ANGLE_STEP;
  /* rotAngleZ += ANGLE_STEP;  */

  mtxRotationX[1][1] = cosf(rotAngleX * 0.5f);
  mtxRotationX[1][2] = sinf(rotAngleX * 0.5f);
  mtxRotationX[2][1] = -sinf(rotAngleX * 0.5f);
  mtxRotationX[2][2] = cosf(rotAngleX * 0.5f);

  mtxRotationY[0][0] = cosf(rotAngleY);
  mtxRotationY[0][2] = sinf(rotAngleY);
  mtxRotationY[2][0] = -sinf(rotAngleY);
  mtxRotationY[2][2] = cosf(rotAngleY);

  /* matRotationZ[0][0] =  cosf(rotAngleZ); */
  /* matRotationZ[0][1] =  sinf(rotAngleZ); */
  /* matRotationZ[1][0] = -sinf(rotAngleZ); */
  /* matRotationZ[1][1] =  cosf(rotAngleZ); */

  for (int i = 0; i < trgc; ++i) {

    triangle = meshCube.triangles[i];

    /* Shift cube's center to point [0,0,0] */
    triangle.v[0].x -= 0.5f;
    triangle.v[1].x -= 0.5f;
    triangle.v[2].x -= 0.5f;

    triangle.v[0].y -= 0.5f;
    triangle.v[1].y -= 0.5f;
    triangle.v[2].y -= 0.5f;

    triangle.v[0].z -= 0.5f;
    triangle.v[1].z -= 0.5f;
    triangle.v[2].z -= 0.5f;

    /* Rotation */
    multiplyVecMtx(&triangle.v[0], mtxRotationX);
    multiplyVecMtx(&triangle.v[1], mtxRotationX);
    multiplyVecMtx(&triangle.v[2], mtxRotationX);

    multiplyVecMtx(&triangle.v[0], mtxRotationY);
    multiplyVecMtx(&triangle.v[1], mtxRotationY);
    multiplyVecMtx(&triangle.v[2], mtxRotationY);

    /* multiplyVecMat(&triangle.v[0], matRotationZ); */
    /* multiplyVecMat(&triangle.v[1], matRotationZ); */
    /* multiplyVecMat(&triangle.v[2], matRotationZ); */

    /* Scale z coordinate to adjust the viewpoint */
    triangle.v[0].z += ZDISTANCE;
    triangle.v[1].z += ZDISTANCE;
    triangle.v[2].z += ZDISTANCE;

    /* Calculate normal */
    line1.x = triangle.v[1].x - triangle.v[0].x;
    line1.y = triangle.v[1].y - triangle.v[0].y;
    line1.z = triangle.v[1].z - triangle.v[0].z;

    line2.x = triangle.v[2].x - triangle.v[0].x;
    line2.y = triangle.v[2].y - triangle.v[0].y;
    line2.z = triangle.v[2].z - triangle.v[0].z;

    normal.x = line1.y * line2.z - line1.z * line2.y;
    normal.y = line1.z * line2.x - line1.x * line2.z;
    normal.z = line1.x * line2.y - line1.y * line2.x;

    normalLength = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

    normal.x /= normalLength;
    normal.y /= normalLength;
    normal.z /= normalLength;

    /* Draw only visible triangles */
    if (normal.x * (triangle.v[0].x - camera.x) +
            normal.y * (triangle.v[0].y - camera.y) +
            normal.z * (triangle.v[0].z - camera.z) <
        0.0f) {

      /* Project the cube on the screen */
      multiplyVecMtx(&triangle.v[0], matProjection);
      multiplyVecMtx(&triangle.v[1], matProjection);
      multiplyVecMtx(&triangle.v[2], matProjection);

      /* Adjust the cube */
      triangle.v[0].x += 1.0f;
      triangle.v[0].y += 1.0f;
      triangle.v[1].x += 1.0f;
      triangle.v[1].y += 1.0f;
      triangle.v[2].x += 1.0f;
      triangle.v[2].y += 1.0f;

      triangle.v[0].x *= 0.5f * WIDTH;
      triangle.v[0].y *= 0.5f * HEIGHT;
      triangle.v[1].x *= 0.5f * WIDTH;
      triangle.v[1].y *= 0.5f * HEIGHT;
      triangle.v[2].x *= 0.5f * WIDTH;
      triangle.v[2].y *= 0.5f * HEIGHT;

      /* Draw triangles */
      drawTriangle(&triangle);
    }
  };
}

void multiplyVecMtx(struct vec3 *vec, float matrix[4][4]) {
  float x = vec->x * matrix[0][0] + vec->y * matrix[1][0] +
            vec->z * matrix[2][0] + matrix[3][0];
  float y = vec->x * matrix[0][1] + vec->y * matrix[1][1] +
            vec->z * matrix[2][1] + matrix[3][1];
  float z = vec->x * matrix[0][2] + vec->y * matrix[1][2] +
            vec->z * matrix[2][2] + matrix[3][2];
  float w = vec->x * matrix[0][3] + vec->y * matrix[1][3] +
            vec->z * matrix[2][3] + matrix[3][3];

  if (w != 0) {
    x /= w;
    y /= w;
    z /= w;
  }
  vec->x = x;
  vec->y = y;
  vec->z = z;
}

void drawTriangle(struct triangle *trg) {
  SDL_RenderDrawLine(renderer, trg->v[0].x, trg->v[0].y, trg->v[1].x,
                     trg->v[1].y);
  SDL_RenderDrawLine(renderer, trg->v[1].x, trg->v[1].y, trg->v[2].x,
                     trg->v[2].y);
  SDL_RenderDrawLine(renderer, trg->v[2].x, trg->v[2].y, trg->v[0].x,
                     trg->v[0].y);
}
