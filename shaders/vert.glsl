#version 410 core

layout(location = 0) in vec3 aPosition; 
layout(location = 1) in vec3 aColor; 

out vec3 color; 

uniform mat4 uRotation; 
uniform mat4 uTranslation; 
uniform mat4 uScale; 
uniform mat4 projection; 

uniform float uTime; 

float rand(vec2 co) {
	// magic numbers !!!
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
	vec3 pos = aPosition;
	mat4 model = uScale * uTranslation * uRotation; 
	
	pos.xy += vec2(rand(pos.xy + uTime), rand(pos.yx + uTime)) * .05; // Add random jitter	
	
	gl_Position = projection * model * vec4(pos, 1.0f); 
	color = aColor; 
}

