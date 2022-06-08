#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <shader.h>
#include <texture.h>

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

	unsigned int shader = CreateShader("./assets/shaders/vert.glsl", "./assets/shaders/vert.glsl");
	glUseProgram(shader);

	//Renderer tests
	//initRenderData();
	//vec2 size = {1.0f, 1.0f};
	//vec2 position = {0.0f, 0.0f};
	//vec4 colour = {1.0f, 0.0f, 0.0f, 1.0f};
	//float textureID = 0.0f;
	//float x = createQuad(size, position, colour, textureID);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
