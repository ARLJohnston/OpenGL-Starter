#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in float texureIndex;


out vec4 vertexColour;
out vec2 texCoord;
out float texIndex;

uniform mat4 Projection;
uniform mat4 View;

void main()
{
	vertexColour = colour;
	texCoord = textureCoord;
	texureIndex = texureIndex;
	gl_Position = Projection* View * Position;
}

