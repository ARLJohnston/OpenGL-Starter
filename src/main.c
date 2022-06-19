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

	//unsigned int shader = CreateShader("./assets/shaders/vert.glsl", "./assets/shaders/frag.glsl");
	//glUseProgram(shader);
	//
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,     0.0f, 0.0f,
	//	0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,1.0f,	    1.0f, 0.0f,
	//	0.5f, 0.5f, 0.0f, 	1.0f, 0.0f, 0.0f,1.0f,	    1.0f, 1.0f,
	//	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,1.0f,	    0.0f, 1.0f
	//};

	//unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	//unsigned int va;
	//glCreateVertexArrays(1, &va);
	//glBindVertexArray(va);

	//unsigned int vb;
	//glGenBuffers(1, &vb);
	//glBindBuffer(GL_ARRAY_BUFFER, vb);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 9* sizeof(float), 0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2,2, GL_FLOAT,GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//unsigned int ib;
	//glGenBuffers(1, &ib);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6* sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//unsigned int texture = LoadTexture("./assets/textures/tex.png");
	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	
	rendererInit("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");
	data();

	/*End test area */

	while(!glfwWindowShouldClose(window))
	{
		//glClear(GL_COLOR_BUFFER_BIT);


		//glUseProgram(shader);
		//glBindVertexArray(va);
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		draw();

		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteVertexArrays(1, &va);
	//glDeleteBuffers(1, &vb);
	//glDeleteBuffers(1, &ib);

	glfwTerminate();
	return 0;
}
