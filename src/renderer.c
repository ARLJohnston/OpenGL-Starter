#include <renderer.h>

struct vertex {
	vec3 position;
	vec4 colour;
	vec2 textureCoords;
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

struct {
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int shader;
} rendererData;

unsigned int texture;

void rendererInit(const char* vertexShaderPath, const char* fragmentShaderPath){
	rendererData.shader = CreateShader(vertexShaderPath, fragmentShaderPath);
	glUseProgram(rendererData.shader);

	glCreateVertexArrays(1, &rendererData.vertexArray);
	glBindVertexArray(rendererData.vertexArray);

	glGenBuffers(1, &rendererData.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rendererData.vertexBuffer);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 9* sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2,2, GL_FLOAT,GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
  glEnableVertexAttribArray(2);

	glGenBuffers(1, &rendererData.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.indexBuffer);
}

void data(){
	float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,     0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,1.0f,      1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,1.0f,      1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,1.0f,      0.0f, 1.0f
  };

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);

	texture = LoadTexture("./assets/textures/tex.png");
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(rendererData.shader);
	glBindVertexArray(rendererData.vertexArray);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
