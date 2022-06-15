#version 460 core

out vec4 colour;

in vec3 v_Colour;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	colour = texture(u_Texture, v_TexCoord);
}

