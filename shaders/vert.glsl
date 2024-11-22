#version 410 core

layout(location = 0) in vec3 aPosition; 
layout(location = 1) in vec3 aColor; 

out vec3 color; 

uniform mat4 uRotation; 
uniform mat4 uTranslation; 
uniform mat4 uScale; 
uniform mat4 projection; 

void main()
{
	mat4 model = uScale * uTranslation * uRotation; 
	gl_Position = projection * model * vec4(aPosition, 1.0f); 
	color = aColor; 
}

