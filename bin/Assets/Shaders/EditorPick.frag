#version 330

out vec4 outputColor;

uniform vec4 PickingColor;

void main()
{
	outputColor = PickingColor;
}
