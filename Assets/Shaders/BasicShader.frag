#version 460 core

out vec4 outFragmentColor;

in vec4 passColor;
in vec2 passTexCoord;

uniform vec4 uColorTint;
uniform sampler2D uTexture;

void main()
{
	outFragmentColor = texture(uTexture, passTexCoord) * passColor * uColorTint;
}