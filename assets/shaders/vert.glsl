#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float texIndex;

out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(position, 1.0);
	v_Colour = colour;
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
}

