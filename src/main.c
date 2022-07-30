#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <renderer.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	updateCamera(window);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	updateZoom(window, xoffset, yoffset);

}

void error_callback(int error, const char *description){
	fprintf(stderr, "(%d) %s\n", error, description);
	fflush(stderr);
}

int main(void){
	glfwInit();

	const char* title = "OpenGL";
	const unsigned int width = 800;
	const unsigned int height = 600;

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window == NULL)
	{
		printf("Failed to initialise GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialise GLAD\n");
		return -1;
	}

	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(error_callback);

	struct Renderer *renderer = rendererInit(200);
	rendererShaderInit(renderer, "assets/shaders/vert.glsl", "assets/shaders/frag.glsl");


	unsigned int texArr[30];

	for(unsigned int i = 0; i < 30; i++){
		char path[28];
		sprintf(path, "%s%d%s", "./assets/textures/tex", i, ".png");
		texArr[i] = LoadTexture(path);
	}

	vec2 quad0Pos = {-1.5f,-0.5f};
	vec2 quad1Pos = {0.5f,-0.5f};

	vec2 quadSize = {1.0f, 1.0f};
	vec4 quadColour = {1.0f, 0.0f, 0.0f, 1.0f};

	vec2 pos;
	vec2 size = {0.25f, 0.25f};

	while(!glfwWindowShouldClose(window))
	{
		rendererClear();

		size.x = 0.25f;
		size.y = 0.25f;
		for(float y = -10.0f; y < 10.0f; y += 0.25f){
			for(float x = -10.0f; x < 10.0f; x += 0.25f){
				pos.x = x;
				pos.y = y;
				vec4 colour = {(x + 10) / 20.0f, 0.2f, (y + 10) / 20.0f, 1.0f};
				rendererDrawQuadColour(renderer, pos, size, colour);
			}
		}


		size.x = 1.0f;
		size.y = 1.0f;
		int i = 0;
		for(int y = 0; y < 6; y++){
			for(int x = 0; x < 5; x++){
				GLuint tex = texArr[i];
				i++;
				pos.x = x;
				pos.y = y;

				rendererDrawQuadTexture(renderer, pos, size, tex);
			}
		}

		rendererFlush(renderer);


		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}    
	rendererTerminate();
	glfwTerminate();
	return 0;
}
