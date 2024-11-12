#version 410 core

layout(location = 0) in vec3 aPosition; 
layout(location = 1) in vec3 aColor; 

out vec3 color; 

// world space
uniform mat4 uRotation; 
uniform mat4 uProjection; 
// view space 
uniform mat4 uTranslation; 
// screen space
uniform mat4 uScale; 

void main()
{
	gl_Position = uScale * uProjection * uTranslation * uRotation * vec4(aPosition, 1.0f); 
	color = aColor; 
}

