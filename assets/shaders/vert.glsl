#version 460 core

layout (location = 0) in vec4 Position;

out vec4 colour;

uniform mat4 Projection;
uniform mat4 View;

void main()
{
	gl_Position = Projection* View * Position;
}

