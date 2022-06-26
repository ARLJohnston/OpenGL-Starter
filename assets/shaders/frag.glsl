#version 460 core

out vec4 colour;

in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Texture[32];

void main()
{
	int index = int(v_TexIndex);
	colour = texture(u_Texture[index], v_TexCoord) * v_Colour;
}

