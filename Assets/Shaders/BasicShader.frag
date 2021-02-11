#version 460 core

out vec4 outFragmentColor;

in vec4 passColor;
in vec2 passTexCoord;

uniform float uTextureLerpRatio;
uniform vec4 uColorTint;
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
	outFragmentColor = mix
	(
		texture(uTexture0, passTexCoord),
		texture(uTexture1, passTexCoord),
		uTextureLerpRatio
	);

	outFragmentColor = outFragmentColor * passColor * uColorTint;
}