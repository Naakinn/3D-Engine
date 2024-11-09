#version 410 core

layout(location = 0) in vec3 position; 
layout(location = 1) in vec3 vertexColors; 

out vec3 v_vertexColors; 

uniform mat4 uTranslation; // zOffset
uniform mat4 uPerspective; 
uniform mat4 uRotation; 
uniform mat4 uScale; 

void main()
{
	v_vertexColors = vertexColors; 

	vec4 newPosition = uScale * uPerspective * uTranslation * uRotation * vec4(position, 1.0f); 
	
	gl_Position = newPosition;
}

