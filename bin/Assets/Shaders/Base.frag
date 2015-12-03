#version 330

smooth in vec4 interpolatedColor;

out vec4 outputColor;

layout (std140) uniform World
{
	vec4 ambientColor;
	float ambientIntensity;
	float lightAttenuation;
	float gammaCorrection;
};

void main()
{
	outputColor = pow(interpolatedColor, vec4(vec3(vec4(gammaCorrection)),1));
}
