#version 460 core

layout (location = 0) out vec4 colour;
in vec4 vertexColour;
in vec2 texCoord;
in float texIndex;

unform sampler2D texSampler[32];

void main()
{
	int index = int(texIndex);
	colour = texture(texSampler[index], texCoord) * vertexColour;
}

