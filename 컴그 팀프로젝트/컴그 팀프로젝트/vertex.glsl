#version 330

uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;

uniform vec3 in_Color;

layout (location = 0)in vec3 in_Position;
layout (location = 1)in vec3 vNormal;

out vec3 ex_Color;
out vec3 FragPos;
out vec3 Normal;



void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(in_Position.x,in_Position.y,in_Position.z,1.0);
	ex_Color = in_Color;
	FragPos = vec3(modelTransform*vec4(in_Position,1.0));
	Normal = vNormal;
}