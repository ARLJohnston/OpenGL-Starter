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

	/* Test Area */

	unsigned int shader = CreateShader("./assets/shaders/vert.glsl", "./assets/shaders/vert.glsl");
	glUseProgram(shader);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int va;
	glCreateVertexArrays(1, &va);
	glBindVertexArray(va);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,2, GL_FLOAT,GL_FALSE, 4 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

	unsigned int ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6* sizeof(unsigned int), indices, GL_STATIC_DRAW);

	/*End test area */

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(va);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &va);
	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);

	glfwTerminate();
	return 0;
}
