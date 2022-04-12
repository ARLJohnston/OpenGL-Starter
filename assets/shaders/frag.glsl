#version 460 core

layout (location = 0) out vec4 colour;
in vec4 vertexColour;

void main()
{
	colour = vertexColour; 
}

