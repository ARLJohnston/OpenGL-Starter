#include <renderer.h>

const unsigned int maxQuadCount = 1000;
const unsigned int maxVertexCount = 4 * maxQuadCount;
const unsigned int maxIndexCount = 6 * maxQuadCount;

typedef struct {
	vec3 position;
	vec4 colour;
	vec2 textureCoords;
	float textureIndex;
} vertex;

struct {
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int shader;
} rendererData;

struct {
	float vertices[200];
	unsigned int textures[32];
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

	glBufferData(GL_ARRAY_BUFFER, maxVertexCount * sizeof(vertex), NULL , GL_DYNAMIC_DRAW);

	unsigned int indices[maxIndexCount];
	unsigned int offset = 0;
	for(unsigned int i = 0; i < maxIndexCount; i+=6){
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;
		offset += 4;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int whiteTexture;
	glCreateTextures(GL_TEXTURE_2D, 1, &whiteTexture);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	unsigned int white = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &white);
	data.textures[0] = whiteTexture;

	for(unsigned int i = 1; i < 32; i++){
		data.textures[i] = 0;
	}

	data.textures[1] = LoadTexture("./assets/textures/tex.png");
	//data.textures[0] = LoadTexture("./assets/textures/tex2.png");

	createQuad(-1.5f, -0.5f, 0.0f);
	createQuad(0.5f, -0.5f, 1.0f);
}

void draw(){

	glBindBuffer(GL_ARRAY_BUFFER, rendererData.vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data.vertices), data.vertices);
	

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(rendererData.shader);
	glBindVertexArray(rendererData.vertexArray);

	//glBindTextureUnit(0,texture);
	//glBindTextureUnit(1,texture2);
	glBindTextures(0,2,&data.textures);
	//for(unsigned int i = 0; i < 32; i++){
	//	glBindTextureUnit(i, data.textures[i]);
	//}


	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void terminate(){
	glDeleteVertexArrays(1, &rendererData.vertexArray);
	glDeleteBuffers(1, &rendererData.vertexBuffer);
	glDeleteBuffers(1, &rendererData.indexBuffer);
}

static float zoom = -1.0f;
static float x = 1.0f;
static float y = 1.0f;

void updateCamera(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		y -= 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		y += 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		x -= 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		x += 0.05f;
	}

	setOrthoMatrix(-5.0*zoom, 5.0*zoom, -5.0*zoom, 5.0*zoom, 0.0f, 10.0f);
	setViewMatrix(x, y);

	glUniformMatrix4fv(glGetUniformLocation(rendererData.shader, "projection"), 1, GL_FALSE, getOrthoMatrix());
	glUniformMatrix4fv(glGetUniformLocation(rendererData.shader, "view"), 1, GL_FALSE, getViewMatrix());
}

void updateZoom(GLFWwindow *window,double xoffset, double yoffset){
	if(yoffset < 0)
	{
		zoom += 0.05f;
	} else {
		zoom -= 0.05f;
	}

	setOrthoMatrix(-5.0*zoom, 5.0*zoom, -5.0*zoom, 5.0*zoom, 0.0f, 10.0f);

	glUniformMatrix4fv(glGetUniformLocation(rendererData.shader, "projection"), 1, GL_FALSE, getOrthoMatrix());

}
