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

float CalculateAttenuation(in vec3 cameraSpacePosition, in vec3 lightPos)
{
	vec3 lightDifference =  lightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);

	return 1.0 / (1.0 + lightAttenuation * lightDistanceSqr);
}

vec4 ComputeLighting(in PerLight light)
{
	vec3 dirToLight = normalize(light.lightPosType.xyz - vPosition.xyz);
	vec3 attenIntensity = light.lightIntensity.xyz;

	if(light.lightPosType.w != 0.0)
	{
		float attenuation = CalculateAttenuation(vPosition.xyz, light.lightPosType.xyz);
		attenIntensity *= attenuation;
	}

	float cosAngIncidence = clamp(dot(normalize(vNormal), dirToLight), 0, 1);
	vec3 viewDirection = -normalize(vPosition.xyz);
	vec3 halfAngle = normalize(dirToLight + viewDirection);
	float angleNormalHalf = acos(dot(halfAngle, normalize(vNormal)));
	float exponent = angleNormalHalf / shininessFactor;
	exponent = -(exponent * exponent);
	float gaussianTerm = exp(exponent);
	gaussianTerm = cosAngIncidence != 0.0 ? gaussianTerm : 0.0;

	return vec4(
		(vColor * attenIntensity * cosAngIncidence) +
		(specularColor.xyz * attenIntensity * gaussianTerm), 1.0);
}

void main()
{
	vec4 accumLighting = vec4(vColor * (ambientColor.xyz * ambientIntensity), 1.0);

	for(int light = 0; light < numberOfLights; light++)
	{
		accumLighting += ComputeLighting(lights[light]);
	}

	vec3 MaxIntensityHDR = vec3(0,0,0);
	for(int light = 0; light < numberOfLights; light++)
	{
		MaxIntensityHDR += lights[light].lightIntensity.xyz;
	}

	accumLighting = accumLighting / vec4(MaxIntensityHDR, 1);

	outputColor = pow(accumLighting, vec4(vec3(vec4(gammaCorrection)),1));
}
