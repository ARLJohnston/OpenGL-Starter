#include <renderer.h>

static struct renderData {
	float *array;
	size_t size;
	size_t used;
} data;

//Should improve to be dynamic.
//float data[256*sizeof(vertex)];

void initRenderData(){
	data->array = malloc(8*sizeof(vertex));
	data->used = 0;
	data->size = 8;
}

void arraySize(){
	if(data->used == data->size){
		data->size *= 2;
		data->array = realloc(data->array, data->size * sizeof(vertex));
	}
}

float createQuad(vec2 size, vec2 position, vec4 colour, float textureID){
	arraySize();

	float quadID = data->used; 
	vertex *quadData = &(data->array + data->used);
	data->used += 4;

	quadData->position = {position.x, position.y, 0.0f};
	quadData->colour = colour;
	quadData->texCoords = {0.0f, 0.0f};
	quadData->texIndex = textureID;
	quadData++;

	quadData->position = {position.x + size.x, position.y, 0.0f};
	quadData->colour = colour;
	quadData->texCoords = {1.0f, 0.0f};
	quadData->texIndex = textureID;
	quadData++;

	quadData->position = {position.x + size.x, position.y + size.y, 0.0f};
	quadData->colour = colour;
	quadData->texCoords = {1.0f, 1.0f};
	quadData->texIndex = textureID;
	quadData++;

	quadData->position = {position.x, position.y + size.y, 0.0f};
	quadData->colour = colour;
	quadData->texCoords = {0.0f, 1.0f};
	quadData->texIndex = textureID;
	quadData++;

	return quadID;
}
