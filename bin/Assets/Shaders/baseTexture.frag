#version 330 core

smooth in vec2 textCoord;
smooth in vec3 vertColor;

out vec4 outputColor;

layout (std140) uniform World
{
	vec4 ambientColor;
	float ambientIntensity;
	float lightAttenuation;
	float gammaCorrection;
};

uniform sampler2D texture0;
//uniform sampler2D texture1;

void main()
{
	//outputColor = pow(vec4(vertColor, 1.0) * mix(texture(texture0, textCoord), texture(texture1, textCoord), 0.5), vec4(vec3(vec4(gammaCorrection)),1));
	outputColor = pow(texture(texture0, textCoord), vec4(vec3(vec4(gammaCorrection)),1));
}
