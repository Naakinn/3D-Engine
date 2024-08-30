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

void multiplyVecMat(struct vec3* vec, float matrix[4][4], struct vec3* ovec);
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
float matRotationZ[4][4]; 


void prepRender() {
	
	fovRad = 1.0 / tanf(fov * 0.5 / 180.0 * PI);
	matProjection[0][0] = aspect * fovRad; 
	matProjection[1][1] = fovRad; 
	
	matRotationZ[2][2] = 1;
	matRotationZ[3][3] = 1;
	
	matRotationX[0][0] = 1;
	matRotationX[3][3] = 1;
	
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
	rotAngle += .01; 
	
	matRotationZ[0][0] = cosf(rotAngle);
	matRotationZ[0][1] = sinf(rotAngle);
	matRotationZ[1][0] = -sinf(rotAngle);
	matRotationZ[1][1] = cosf(rotAngle);
		
	matRotationX[1][1] = cosf(rotAngle * 0.5);
	matRotationX[1][2] = sinf(rotAngle * 0.5);
	matRotationX[2][1] = -sinf(rotAngle * 0.5);
	matRotationX[2][2] = cosf(rotAngle * 0.5);
	
	for (int i = 0; i < trgnum; ++i) {
		
		struct triangle tri = meshCube.triangles[i]; 
		struct triangle trgRotatedZ, trgRotatedX, trgTranslated, trgProjected; 
		
		multiplyVecMat(&tri.v[0], matRotationZ, &trgRotatedZ.v[0]);
		multiplyVecMat(&tri.v[1], matRotationZ, &trgRotatedZ.v[1]);
		multiplyVecMat(&tri.v[2], matRotationZ, &trgRotatedZ.v[2]);
		
		multiplyVecMat(&trgRotatedZ.v[0], matRotationX, &trgRotatedX.v[0]);
		multiplyVecMat(&trgRotatedZ.v[1], matRotationX, &trgRotatedX.v[1]);
		multiplyVecMat(&trgRotatedZ.v[2], matRotationX, &trgRotatedX.v[2]);
		/*multiplyVecMat(&tri.v[0], matRotationX, &trgRotatedX.v[0]);*/
		/*multiplyVecMat(&tri.v[1], matRotationX, &trgRotatedX.v[1]);*/
		/*multiplyVecMat(&tri.v[2], matRotationX, &trgRotatedX.v[2]);*/
		
		
		trgTranslated = trgRotatedX; 
		
		trgTranslated.v[0].z = trgRotatedX.v[0].z + 3.0; 
		trgTranslated.v[1].z = trgRotatedX.v[1].z + 3.0; 
		trgTranslated.v[2].z = trgRotatedX.v[2].z + 3.0; 
		
		multiplyVecMat(&trgTranslated.v[0], matProjection, &trgProjected.v[0]);
		multiplyVecMat(&trgTranslated.v[1], matProjection, &trgProjected.v[1]);
		multiplyVecMat(&trgTranslated.v[2], matProjection, &trgProjected.v[2]);
		
		trgProjected.v[0].x += 1.0; trgProjected.v[0].y += 1.0; 
		trgProjected.v[1].x += 1.0; trgProjected.v[1].y += 1.0; 
		trgProjected.v[2].x += 1.0; trgProjected.v[2].y += 1.0; 

		trgProjected.v[0].x *= 0.5 * WIDTH; 
		trgProjected.v[0].y *= 0.5 * HEIGHT; 
		trgProjected.v[1].x *= 0.5 * WIDTH; 
		trgProjected.v[1].y *= 0.5 * HEIGHT; 
		trgProjected.v[2].x *= 0.5 * WIDTH; 
		trgProjected.v[2].y *= 0.5 * HEIGHT; 
		
		drawTrg(&trgProjected);
	};
}

void multiplyVecMat(struct vec3* vec, float matrix[4][4], struct vec3* ovec) {
	ovec->x = vec->x * matrix[0][0] + vec->y * matrix[1][0] + vec->z * matrix[2][0] + matrix[3][0]; 
	ovec->y = vec->x * matrix[0][1] + vec->y * matrix[1][1] + vec->z * matrix[2][1] + matrix[3][1]; 
	ovec->z = vec->x * matrix[0][2] + vec->y * matrix[1][2] + vec->z * matrix[2][2] + matrix[3][2]; 
	float w = vec->x * matrix[0][3] + vec->y * matrix[1][3] + vec->z * matrix[2][3] + matrix[3][3]; 

	if (w != 0) {
		ovec->x /= w; 
		ovec->y /= w; 
		ovec->z /= w; 
	}
}

void drawTrg(struct triangle* trg) {
	SDL_RenderDrawLine(renderer, trg->v[0].x, trg->v[0].y, trg->v[1].x, trg->v[1].y);
	SDL_RenderDrawLine(renderer, trg->v[1].x, trg->v[1].y, trg->v[2].x, trg->v[2].y);
	SDL_RenderDrawLine(renderer, trg->v[2].x, trg->v[2].y, trg->v[0].x, trg->v[0].y);
}

