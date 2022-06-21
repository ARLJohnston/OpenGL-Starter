#include <renderer.h>

#define MAX_VERTICES 128

typedef struct {
	vec3 position;
	vec4 colour;
	vec2 textureCoords;
	float textureIndex;
} vertex;

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4
};

struct {
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int shader;
} rendererData;

struct {
	float vertices[200];
	unsigned int count;
} data;

unsigned int texture;
unsigned int texture2;

void createQuad(float x, float y, float textureIndex){

	float size = 1.0f;

	vertex* objectPtr = (void*) &data.vertices + (data.count * 4 * sizeof(vertex));

	vec4 colour = {1.0f, 0.0f, 0.0f, 1.0f};

	objectPtr->position.x = x;
	objectPtr->position.y = y;
	objectPtr->position.z = 0.0f;
	objectPtr->colour = colour;
	objectPtr->textureCoords.x = 0.0f;
	objectPtr->textureCoords.y = 0.0f;
	objectPtr->textureIndex = textureIndex;
	objectPtr++;

	objectPtr->position.x = x + size;
	objectPtr->position.y = y;
	objectPtr->position.z = 0.0f;
	objectPtr->colour = colour;
	objectPtr->textureCoords.x = 1.0f;
	objectPtr->textureCoords.y = 0.0f;
	objectPtr->textureIndex = textureIndex;
	objectPtr++;

	objectPtr->position.x = x + size;
	objectPtr->position.y = y + size;
	objectPtr->position.z = 0.0f;
	objectPtr->colour = colour;
	objectPtr->textureCoords.x = 1.0f;
	objectPtr->textureCoords.y = 1.0f;
	objectPtr->textureIndex = textureIndex;
	objectPtr++;

	objectPtr->position.x = x;
	objectPtr->position.y = y + size;
	objectPtr->position.z = 0.0f;
	objectPtr->colour = colour;
	objectPtr->textureCoords.x = 0.0f;
	objectPtr->textureCoords.y = 1.0f;
	objectPtr->textureIndex = textureIndex;
	objectPtr++;

	data.count++;
}

void rendererInit(const char* vertexShaderPath, const char* fragmentShaderPath){
	rendererData.shader = CreateShader(vertexShaderPath, fragmentShaderPath);
	glUseProgram(rendererData.shader);

	glCreateVertexArrays(1, &rendererData.vertexArray);
	glBindVertexArray(rendererData.vertexArray);

	glGenBuffers(1, &rendererData.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rendererData.vertexBuffer);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
  glEnableVertexAttribArray(0);                  
  glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);                  
  glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(7 * sizeof(float)));
  glEnableVertexAttribArray(2);                  
	glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glGenBuffers(1, &rendererData.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.indexBuffer);

	unsigned int location=glGetUniformLocation(rendererData.shader,"u_Texture");
	int samplers[32];
	for(int i = 0; i < 32; i++){
		samplers[i] = i;
	}
	glUniform1iv(location, 32, samplers);

	glBufferData(GL_ARRAY_BUFFER, 1000 * sizeof(vertex), NULL , GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	texture = LoadTexture("./assets/textures/tex.png");
	texture2 = LoadTexture("./assets/textures/tex2.png");

	createQuad(-1.5f, -0.5f, 0.0f);
	createQuad(0.5f, -0.5f, 1.0f);
}

void draw(){

	glBindBuffer(GL_ARRAY_BUFFER, rendererData.vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data.vertices), data.vertices);
	

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(rendererData.shader);
	glBindVertexArray(rendererData.vertexArray);

	glBindTextureUnit(0,texture);
	glBindTextureUnit(1,texture2);


	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void terminate(){
	glDeleteVertexArrays(1, &rendererData.vertexArray);
	glDeleteBuffers(1, &rendererData.vertexBuffer);
	glDeleteBuffers(1, &rendererData.indexBuffer);
}
