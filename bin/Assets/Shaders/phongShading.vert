#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
//layout (location = 3) in vec3 color;

smooth out vec3 v_Position;
smooth out vec3 v_Normal;
smooth out vec2 v_TexCoords;
smooth out vec3 v_Color;

layout (std140) uniform GlobalMatrices
{
	mat4 cameraToClipMatrix;
	mat4 worldToCameraMatrix;
};

//layout (std140) uniform Material
//{
//	vec3 diffuse;
//	vec3 specular;
//	float shininess; // 2~256
//};

struct Material
{
	vec3 diffuseColor;
	vec3 specularColor;
	sampler2D diffuse0;
	sampler2D specular0;
	float shininess;
};
uniform Material material;

uniform mat4 modelToWorldMatrix;
uniform mat3 normalMatrix;

void main()
{
	mat4 modelToCameraMatrix = worldToCameraMatrix * modelToWorldMatrix;

	gl_Position = cameraToClipMatrix * modelToCameraMatrix * vec4(position, 1.0f);

	v_Position = vec3(modelToCameraMatrix * vec4(position, 1.0f));
	v_Normal = mat3(worldToCameraMatrix) * normalMatrix * normal; // mat3(transpose(inverse(modelToCameraMatrix))) * normal;
	v_TexCoords = texCoords;
	v_Color = material.diffuseColor;
}
