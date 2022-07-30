#include <renderer.h>
#include <stdio.h>

typedef struct {
	vec3 position;
	vec4 colour;
	vec2 textureCoords;
	float textureIndex;
} vertex;

struct Renderer {
	uint32_t maxQuadsPerBatch;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	unsigned int shader;

	vertex* buffer;
	uint32_t quadCount;

	uint32_t* textureSlots;
	int textureCount;
};

static struct Renderer renderer;
static uint32_t shader;
static uint32_t slots;

struct Renderer* rendererInit(int maxQuadsPerBatch){
	struct Renderer *irenderer = &renderer;
	irenderer->maxQuadsPerBatch = maxQuadsPerBatch;
	irenderer->quadCount = 0;

	unsigned int vao;
	glCreateVertexArrays(1, &vao);

	glGenVertexArrays(1, &irenderer->vao);
	glBindVertexArray(irenderer->vao);

	glGenBuffers(1, &irenderer->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, irenderer->vbo);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);                  
  glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(7 * sizeof(float)));
  glEnableVertexAttribArray(2);                  
  glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(9 * sizeof(float)));
  glEnableVertexAttribArray(3);

	glGenBuffers(1, &irenderer->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, irenderer->ibo);

	irenderer->buffer = malloc(sizeof(vertex) * 4 * maxQuadsPerBatch);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 4 * maxQuadsPerBatch, NULL, GL_DYNAMIC_DRAW);

	uint32_t* indexBuffer = malloc(sizeof(uint32_t) * 6 * maxQuadsPerBatch);
	unsigned int offset = 0;
	for(int i = 0; i < 6 * maxQuadsPerBatch; i += 6){
		indexBuffer[i + 0] = 0 + offset;
		indexBuffer[i + 1] = 1 + offset;
		indexBuffer[i + 2] = 2 + offset;

		indexBuffer[i + 3] = 2 + offset;
		indexBuffer[i + 4] = 3 + offset;
		indexBuffer[i + 5] = 0 + offset;

		offset += 4;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6 * maxQuadsPerBatch, indexBuffer, GL_STATIC_DRAW);
	free(indexBuffer);

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slots);
	irenderer->textureSlots = malloc(sizeof(uint32_t) * slots);


	unsigned int whiteTexture;
	glCreateTextures(GL_TEXTURE_2D, 1, &whiteTexture);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	unsigned int white = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &white);
	irenderer->textureSlots[0] = whiteTexture;
	irenderer->textureCount++;

	for (unsigned int i = 1; i < slots; i++) {
		irenderer->textureSlots[i] = 0;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	return irenderer;
}

void rendererDrawQuadColour(struct Renderer *renderer, vec2 position, vec2 size, vec4 colour){
	int offset = renderer->quadCount * 4;
	float textureIndex = 0;

	unsigned int i = 0;

	renderer->buffer[offset + i].position.x = position.x;
	renderer->buffer[offset + i].position.y = position.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 0.0f;
	renderer->buffer[offset + i].textureCoords.y = 0.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	i++;

	renderer->buffer[offset + i].position.x = position.x + size.x;
	renderer->buffer[offset + i].position.y = position.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 1.0f;
	renderer->buffer[offset + i].textureCoords.y = 0.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	i++;

	renderer->buffer[offset + i].position.x = position.x + size.x;
	renderer->buffer[offset + i].position.y = position.y + size.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 1.0f;
	renderer->buffer[offset + i].textureCoords.y = 1.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	i++;

	renderer->buffer[offset + i].position.x = position.x;
	renderer->buffer[offset + i].position.y = position.y + size.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 0.0f;
	renderer->buffer[offset + i].textureCoords.y = 1.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;

	renderer->quadCount++;
	if(renderer->quadCount >= renderer->maxQuadsPerBatch){
		rendererFlush(renderer);
	}
}

void rendererDrawQuadTexture(struct Renderer *renderer, vec2 position, vec2 size, unsigned int textureID){
	int offset = renderer->quadCount * 4;
	vec4 colour = {1.0f, 1.0f, 1.0f, 1.0f };

	if(renderer->textureCount >= slots || renderer->quadCount >= renderer->maxQuadsPerBatch){
		rendererFlush(renderer);
	}

	float textureIndex = 0.0f;
	for(unsigned int i = 1; i < slots; i++){
		if (renderer->textureSlots[i] == textureID) {
			textureIndex = (float)i;
			break;
		}
	}

	if(textureIndex == 0.0f){
		textureIndex = (float)(renderer->textureCount);
		renderer->textureSlots[renderer->textureCount] = textureID;
		renderer->textureCount++;
	}

	int i = 0;
	renderer->buffer[offset + i].position.x = position.x;
	renderer->buffer[offset + i].position.y = position.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 0.0f;
	renderer->buffer[offset + i].textureCoords.y = 0.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	i++;

	renderer->buffer[offset + i].position.x = position.x + size.x;
	renderer->buffer[offset + i].position.y = position.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 1.0f;
	renderer->buffer[offset + i].textureCoords.y = 0.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	i++;

	renderer->buffer[offset + i].position.x = position.x + size.x;
	renderer->buffer[offset + i].position.y = position.y + size.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 1.0f;
	renderer->buffer[offset + i].textureCoords.y = 1.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	i++;

	renderer->buffer[offset + i].position.x = position.x;
	renderer->buffer[offset + i].position.y = position.y + size.y;
	renderer->buffer[offset + i].position.z = 0.0f;
	renderer->buffer[offset + i].colour = colour;
	renderer->buffer[offset + i].textureCoords.x = 0.0f;
	renderer->buffer[offset + i].textureCoords.y = 1.0f;
	renderer->buffer[offset + i].textureIndex = textureIndex;
	
	renderer->quadCount++;
}

void rendererFlush(struct Renderer *renderer){
	int bufferSize = sizeof(vertex) * 4 * renderer->quadCount;
	int count = 6 * renderer->quadCount;

	glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, renderer->buffer);

	glBindTextures(0, renderer->textureCount, renderer->textureSlots);
	glBindVertexArray(renderer->vao);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);

	renderer->quadCount = 0;
	renderer->textureCount = 1;
}

void rendererShaderInit(struct Renderer *renderer, const char* vertexShaderPath, const char* fragmentShaderPath){
	shader = CreateShader(vertexShaderPath, fragmentShaderPath);
	glUseProgram(shader);
	renderer->shader = shader;

	unsigned int location = glGetUniformLocation(renderer->shader, "u_Texture");
	int *samplers = (int*)malloc(slots*sizeof(int));

	for(int i = 0; i < slots; i++){
		samplers[i] = i;
	}
	glUniform1iv(location, slots, samplers);
	free(samplers);
}

void rendererClear(){
		glClear(GL_COLOR_BUFFER_BIT);
}

void rendererTerminate(){
	glDeleteVertexArrays(1, &renderer.vao);
	glDeleteBuffers(1, &renderer.vbo);
	glDeleteBuffers(1, &renderer.ibo);
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

	if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		zoom+= 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		zoom-= 0.05f;
	}

	setOrthoMatrix(-5.0*zoom, 5.0*zoom, -5.0*zoom, 5.0*zoom, -1.0f, 10.0f);
	setViewMatrix(x, y);

	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, getOrthoMatrix());
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, getViewMatrix());
}

void updateZoom(GLFWwindow *window,double xoffset, double yoffset){
	if(yoffset < 0)
	{
		zoom += 0.05f;
	} else {
		zoom -= 0.05f;
	}

	setOrthoMatrix(-5.0*zoom, 5.0*zoom, -5.0*zoom, 5.0*zoom, 0.0f, 10.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, getOrthoMatrix());

}
