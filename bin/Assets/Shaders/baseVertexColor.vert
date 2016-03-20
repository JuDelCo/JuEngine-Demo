#version 330 core

layout (location = 0) in vec4 position;
layout (location = 3) in vec3 color;

smooth out vec4 interpolatedColor;

layout (std140) uniform GlobalMatrices
{
	mat4 cameraToClipMatrix;
	mat4 worldToCameraMatrix;
};

uniform mat4 modelToWorldMatrix;

void main()
{
	gl_Position = cameraToClipMatrix * worldToCameraMatrix * modelToWorldMatrix * position;
	interpolatedColor = vec4(color, 1.0);
}
