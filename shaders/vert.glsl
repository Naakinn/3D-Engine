#version 410 core

layout(location = 0) in vec3 aPosition; // Index of the generic vertex attribute for vertices
layout(location = 1) in vec3 aColor; // Index of the generic vertex attribute for color 

out vec3 color; 

uniform mat4 uRotation; 
uniform mat4 uTranslation; 
uniform mat4 uScale; 
uniform mat4 uProjection; 

// uniform float uTime; 

float rand(vec2 co) {
	// magic numbers !!!
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
	vec3 pos = aPosition;
	mat4 model = uScale * uTranslation * uRotation; 
	mat4 projection = uProjection; 
	gl_Position = projection * model * vec4(pos, 1.0f); 
	color = aColor; 
}

