#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
// TODO
//layout (location = 2) in vec2 texCoord;
//layout (location = 3) in vec3 color;

out vec4 vPosition;
out vec3 vNormal;
out vec3 vColor;

layout (std140) uniform GlobalMatrices
{
	mat4 cameraToClipMatrix;
	mat4 worldToCameraMatrix;
};

layout (std140) uniform World
{
	vec4 ambientColor;
	float ambientIntensity;
	float lightAttenuation;
	float gammaCorrection;
};

layout (std140) uniform Material
{
	vec4 diffuseColor;
	vec4 specularColor;
	float shininessFactor;
};

uniform mat4 modelToWorldMatrix;

void main()
{
	mat4 modelToCameraMatrix = worldToCameraMatrix * modelToWorldMatrix;

	gl_Position = cameraToClipMatrix * modelToCameraMatrix * position;

	vPosition = modelToCameraMatrix * position;
	vNormal = normalize(mat3(modelToCameraMatrix) * normal);
	vColor = vec3(diffuseColor);
}
