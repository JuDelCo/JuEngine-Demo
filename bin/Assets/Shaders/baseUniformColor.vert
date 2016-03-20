#version 330 core

layout (location = 0) in vec4 position;

smooth out vec4 interpolatedColor;

layout (std140) uniform GlobalMatrices
{
	mat4 cameraToClipMatrix;
	mat4 worldToCameraMatrix;
};

layout (std140) uniform Material
{
	vec3 diffuseColor;
	vec3 specularColor;
	float shininessFactor;
};

uniform mat4 modelToWorldMatrix;

void main()
{
	gl_Position = cameraToClipMatrix * worldToCameraMatrix * modelToWorldMatrix * position;
	interpolatedColor = vec4(diffuseColor, 1.0);
}
