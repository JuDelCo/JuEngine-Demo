#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec3 color;

smooth out vec4 interpolatedColor;

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

// ===========================================

const int numberOfLights = 5;

struct PerLight
{
	vec4 lightPosType;
	vec4 lightIntensity;
};

layout (std140) uniform Light
{
	PerLight lights[numberOfLights];
};

// ===========================================

// TODO
//uniform vec3 lightPos;
//uniform vec3 lightColor;

void main()
{
	mat4 modelToCameraMatrix = worldToCameraMatrix * modelToWorldMatrix;

	gl_Position = cameraToClipMatrix * modelToCameraMatrix * position;

	vec3 normalCameraSpace = normalize(mat3(modelToCameraMatrix) * normal);
	vec3 dirToLight = normalize(lights[0].lightPosType.xyz - vec3(modelToWorldMatrix * position));
	float cosAngIncidence = clamp(dot(normalCameraSpace, mat3(worldToCameraMatrix) * dirToLight), 0, 1);

	interpolatedColor = vec4((color * lights[0].lightIntensity.xyz * cosAngIncidence) + (color * ambientColor.xyz * ambientIntensity), 1);
}
