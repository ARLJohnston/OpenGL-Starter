#include <renderer.h>

struct vertex {
	vec3 position;
	vec4 colour;
	vec2 textureCoords;
	unsigned int textureIndex;
};

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

unsigned int texture;
unsigned int texture2;

void rendererInit(const char* vertexShaderPath, const char* fragmentShaderPath){
	rendererData.shader = CreateShader(vertexShaderPath, fragmentShaderPath);
	glUseProgram(rendererData.shader);

	glCreateVertexArrays(1, &rendererData.vertexArray);
	glBindVertexArray(rendererData.vertexArray);

	glGenBuffers(1, &rendererData.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rendererData.vertexBuffer);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 10* sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2,2, GL_FLOAT,GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));
  glEnableVertexAttribArray(2);
	glVertexAttribPointer(3,1,GL_FLOAT, GL_FALSE, 10* sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glGenBuffers(1, &rendererData.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.indexBuffer);

	unsigned int location=glGetUniformLocation(rendererData.shader,"u_Texture");
	int samplers[32];
	for(int i = 0; i < 32; i++){
		samplers[i] = i;
	}
	glUniform1iv(location, 32, samplers);
}

void data(){
	float vertices[] = {
    -1.5f, -0.5f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,	0.0f, 
    -0.5f, -0.5f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,	0.0f,
    -0.5f,  0.5f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,	0.0f,
    -1.5f,  0.5f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,	0.0f,

     0.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f ,1.0f, 
     1.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f ,1.0f,
     1.5f,  0.5f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f ,1.0f,
     0.5f,  0.5f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f ,1.0f
  };

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	texture = LoadTexture("./assets/textures/tex.png");
	texture2 = LoadTexture("./assets/textures/tex2.png");
}

int createQuad(vec2 transform, vec2 size, vec4 colour, const char* texturePath){
	//unsigned int texture = LoadTexture(texturePath);

	//vertex quad[4];

	//for(int i = 0; i < 4; i++){
	//	quad[i].colour = colour;
	//}

	//quad[0].position.x = transform.x;
	//quad[0].position.y = transform.y;
	//quad[0].position.z = 0.0f;
	//quad[0].textureCoords = {0.0f, 0.0f};

	//quad[1].position.x = transform.x + size.x;
	//quad[1].position.y = transform.y;
	//quad[1].position.z = 0.0f;
	//quad[1].textureCoords = {1.0f, 0.0f};

	//quad[2].position.x = transform.x + size.x;
	//quad[2].position.y = transform.y + size.y;
	//quad[2].position.z = 0.0f;
	//quad[2].textureCoords = {1.0f, 1.0f};

	//quad[3].position.x = transform.x;
	//quad[3].position.y = transform.y + size.y;
	//quad[3].position.z = 0.0f;
	//quad[3].textureCoords = {0.0f, 1.0f};
}

void draw(){
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
