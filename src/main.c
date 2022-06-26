#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
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

	rendererInit("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");

	while(!glfwWindowShouldClose(window))
	{
		draw();

		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}
