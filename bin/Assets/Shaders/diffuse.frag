#version 330 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;

out vec4 outputColor;

layout (std140) uniform GlobalMatrices
{
	mat4 cameraToClipMatrix;
	mat4 worldToCameraMatrix;
};

layout (std140) uniform World
{
	vec3 ambientLight;
	float lightAttenuation;
};

uniform mat4 modelToWorldMatrix;

// TODO
//uniform vec3 lightPos;
//uniform vec3 lightColor;

float CalculateAttenuation(in vec3 cameraSpacePosition, in vec3 cameraSpaceLightPos)
{
	vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);

	return 1.0 / (1.0 + lightAttenuation * lightDistanceSqr);
}

void main()
{
	vec3 dirToLight = normalize(vec3(worldToCameraMatrix * vec4(lightPos, 1.0) - vPosition));
	float cosAngIncidence = clamp(dot(normalize(vNormal), dirToLight), 0, 1);
	float attenuation = CalculateAttenuation(vec3(vPosition), vec3(worldToCameraMatrix * vec4(lightPos, 1.0)));

	outputColor = vec4((vColor * attenuation * cosAngIncidence) + (vColor * ambientLight), 1.0);
}
