#version 460 core

out vec4 outFragmentColor;

in vec4 passColor;

void main()
{
	outFragmentColor = passColor;
}