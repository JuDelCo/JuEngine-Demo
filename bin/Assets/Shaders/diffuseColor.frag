#version 330 core

smooth in vec3 v_Position;
smooth in vec3 v_Normal;
smooth in vec2 v_TexCoords;
smooth in vec3 v_Color;

out vec4 frag_color;

void main()
{
	frag_color = vec4(v_Color, 1.0f);
}
