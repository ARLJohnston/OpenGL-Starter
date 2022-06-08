#ifndef RENDERER
#define RENDERER

#include <vector.h>
#include <glad/glad.h>

struct vertex {
	vec3 position;
	vec4 colour;
	vec2 texCoords;
	float texIndex;
};

void initRenderData();

float createQuad(vec2 size, vec2 position, vec4 colour, float textureID);
#endif
