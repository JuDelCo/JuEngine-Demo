#version 330 core

smooth in vec3 v_Position;
smooth in vec3 v_Normal;
smooth in vec2 v_TexCoords;
smooth in vec3 v_Color;
smooth in vec3 v_LightColor;

out vec4 frag_color;

struct Material
{
	sampler2D diffuse0;
};
uniform Material material;

void main()
{
	vec3 result = v_LightColor * v_Color; // * vec3(texture(material.diffuse0, v_TexCoords));
	frag_color = vec4(result, 1.0f);
}
