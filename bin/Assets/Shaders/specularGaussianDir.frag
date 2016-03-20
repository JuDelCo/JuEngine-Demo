#version 330 core

smooth in vec4 vPosition;
smooth in vec3 vNormal;
smooth in vec3 vColor;

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

layout (std140) uniform Material
{
	vec3 diffuseColor;
	vec3 specularColor;
	float shininessFactor; // 0.1
};

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
	vec3 dirToLight = normalize(mat3(worldToCameraMatrix) * vec3(0,1,0));
	float attenuation = CalculateAttenuation(vPosition.xyz, vec3(worldToCameraMatrix * vec4(lightPos, 1.0)));
	vec3 attenIntensity = lightColor * attenuation * 7;

	float cosAngIncidence = clamp(dot(normalize(vNormal), dirToLight), 0, 1);
	vec3 viewDirection = -normalize(vPosition.xyz);
	vec3 halfAngle = normalize(dirToLight + viewDirection);
	float angleNormalHalf = acos(dot(halfAngle, normalize(vNormal)));
	float exponent = angleNormalHalf / shininessFactor;
	exponent = -(exponent * exponent);
	float gaussianTerm = exp(exponent);
	gaussianTerm = cosAngIncidence != 0.0 ? gaussianTerm : 0.0;

	outputColor = vec4(
		(vColor * attenIntensity * cosAngIncidence) +
		(specularColor * attenIntensity * gaussianTerm) +
		(vColor * ambientLight), 1.0);
}
