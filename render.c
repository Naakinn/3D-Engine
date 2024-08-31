#include "render.h"
#include "sdl.h"


extern SDL_Renderer* renderer; 

struct vec3 { 
	float x, y, z; 
};

struct triangle {
	struct vec3 v[3]; 
};

struct mesh {
	struct triangle* triangles; 
} meshCube;

void multiplyVecMat(struct vec3* vec, float matrix[4][4]);
void drawTrg(struct triangle* trg); 

static const float dNear = 1.0;
static const float dFar = 1000.0; 
static const float aspect =  HEIGHT / WIDTH; 
static const float fov = 90.0; 
static unsigned int trgnum = 0; 
static float fovRad; 
static float rotAngle = 1.0; 

float matProjection[4][4] = {
	{ 0, 0, 0,                              0 },
	{ 0, 0,                                 0 },
	{ 0, 0, dFar / ( dFar - dNear ),        1 },
	{ 0, 0, -dFar * dNear / (dFar - dNear), 0 },
};
float matRotationX[4][4]; 
float matRotationY[4][4]; 
float matRotationZ[4][4]; 

void prepRender() {
	
	/* Calculations in runtime, but not in render loop */
	fovRad = 1.0 / tanf(fov * 0.5 / 180.0 * PI);
	matProjection[0][0] = aspect * fovRad; 
	matProjection[1][1] = fovRad; 
	
	matRotationX[0][0] = 1;
	matRotationX[3][3] = 1;

	matRotationY[1][1] = 1;
	matRotationY[3][3] = 1;
	
	matRotationZ[2][2] = 1;
	matRotationZ[3][3] = 1;
	
	/* Some data */ 
	enum { size = 36 }; 
	struct vec3 vectors[size] = {
		0.0, 0.0, 0.0,	0.0, 1.0, 0.0,	1.0, 1.0, 0.0,
		0.0, 0.0, 0.0,  1.0, 1.0, 0.0,	1.0, 0.0, 0.0,

		1.0, 0.0, 0.0,  1.0, 1.0, 0.0,	1.0, 1.0, 1.0, 
		1.0, 0.0, 0.0,  1.0, 1.0, 1.0,	1.0, 0.0, 1.0,

		1.0, 0.0, 1.0,  1.0, 1.0, 1.0,	0.0, 1.0, 1.0, 
		1.0, 0.0, 1.0,  0.0, 1.0, 1.0,	0.0, 0.0, 1.0,

		0.0, 0.0, 1.0,  0.0, 1.0, 1.0,	0.0, 1.0, 0.0, 
		0.0, 0.0, 1.0,	0.0, 1.0, 0.0,	0.0, 0.0, 0.0, 

		0.0, 1.0, 0.0,	0.0, 1.0, 1.0,	1.0, 1.0, 1.0, 
		0.0, 1.0, 0.0, 	1.0, 1.0, 1.0,	1.0, 1.0, 0.0,

		1.0, 0.0, 1.0, 	0.0, 0.0, 1.0,	0.0, 0.0, 0.0, 
		1.0, 0.0, 1.0, 	0.0, 0.0, 0.0,	1.0, 0.0, 0.0,
	};
	trgnum = size / 3; 
	meshCube.triangles = (struct triangle*)malloc(sizeof(struct triangle) * trgnum);
	
	int k = 0; 
	for (int i = 0; i < trgnum; ++i) {
		for (int j = 0; j < 3; ++j) {
			meshCube.triangles[i].v[j] = vectors[k]; 
			++k;
		}
	}
}


void render() {
	/* Runtime calculations during render */
	rotAngle += .01; 
	
	matRotationX[1][1] = cosf(rotAngle * 0.5);
	matRotationX[1][2] = sinf(rotAngle * 0.5);
	matRotationX[2][1] = -sinf(rotAngle * 0.5);
	matRotationX[2][2] = cosf(rotAngle * 0.5);

	matRotationY[0][0] = cosf(rotAngle); 
	matRotationY[0][2] = sinf(rotAngle); 
	matRotationY[2][0] = -sinf(rotAngle); 
	matRotationY[2][2] = cosf(rotAngle); 
	
	matRotationZ[0][0] = cosf(rotAngle);
	matRotationZ[0][1] = sinf(rotAngle);
	matRotationZ[1][0] = -sinf(rotAngle);
	matRotationZ[1][1] = cosf(rotAngle);
	
	for (int i = 0; i < trgnum; ++i) {
		
		struct triangle triangle = meshCube.triangles[i]; 
		
		/* Shift cube's center to point [0,0,0] */
		triangle.v[0].x -= .5;
		triangle.v[1].x -= .5;
		triangle.v[2].x -= .5;
		
		triangle.v[0].y -= .5;
		triangle.v[1].y -= .5;
		triangle.v[2].y -= .5;
		
		triangle.v[0].z -= .5;
		triangle.v[1].z -= .5;
		triangle.v[2].z -= .5;
		
		/* Rotation */
		multiplyVecMat(&triangle.v[0], matRotationX);
		multiplyVecMat(&triangle.v[1], matRotationX);
		multiplyVecMat(&triangle.v[2], matRotationX);
		
		multiplyVecMat(&triangle.v[0], matRotationY);
		multiplyVecMat(&triangle.v[1], matRotationY);
		multiplyVecMat(&triangle.v[2], matRotationY);

		multiplyVecMat(&triangle.v[0], matRotationZ);
		multiplyVecMat(&triangle.v[1], matRotationZ);
		multiplyVecMat(&triangle.v[2], matRotationZ);
		
		/* Scale z coordinate to adjust the view */ 
		triangle.v[0].z += 3.0; 
		triangle.v[1].z += 3.0; 
		triangle.v[2].z += 3.0; 
		
		/* Project the cube on the screen */ 
		multiplyVecMat(&triangle.v[0], matProjection);
		multiplyVecMat(&triangle.v[1], matProjection);
		multiplyVecMat(&triangle.v[2], matProjection);
		
		/* Adjust the cube */
		triangle.v[0].x += 1.0; triangle.v[0].y += 1.0; 
		triangle.v[1].x += 1.0; triangle.v[1].y += 1.0; 
		triangle.v[2].x += 1.0; triangle.v[2].y += 1.0; 

		triangle.v[0].x *= 0.5 * WIDTH; 
		triangle.v[0].y *= 0.5 * HEIGHT; 
		triangle.v[1].x *= 0.5 * WIDTH; 
		triangle.v[1].y *= 0.5 * HEIGHT; 
		triangle.v[2].x *= 0.5 * WIDTH; 
		triangle.v[2].y *= 0.5 * HEIGHT; 
		
		/* Draw triangles */
		drawTrg(&triangle);
	};
}

void multiplyVecMat(struct vec3* vec, float matrix[4][4]) {
	float x = vec->x * matrix[0][0] + vec->y * matrix[1][0] + vec->z * matrix[2][0] + matrix[3][0]; 
	float y = vec->x * matrix[0][1] + vec->y * matrix[1][1] + vec->z * matrix[2][1] + matrix[3][1]; 
	float z = vec->x * matrix[0][2] + vec->y * matrix[1][2] + vec->z * matrix[2][2] + matrix[3][2]; 
	float w = vec->x * matrix[0][3] + vec->y * matrix[1][3] + vec->z * matrix[2][3] + matrix[3][3]; 
	
	if (w != 0) {
		x /= w; 
		y /= w; 
		z /= w; 
	}
	vec->x = x; 
	vec->y = y; 
	vec->z = z; 
}

void drawTrg(struct triangle* trg) {
	SDL_RenderDrawLine(renderer, trg->v[0].x, trg->v[0].y, trg->v[1].x, trg->v[1].y);
	SDL_RenderDrawLine(renderer, trg->v[1].x, trg->v[1].y, trg->v[2].x, trg->v[2].y);
	SDL_RenderDrawLine(renderer, trg->v[2].x, trg->v[2].y, trg->v[0].x, trg->v[0].y);
	/* SDL_RenderDrawLine(renderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);  */
}

