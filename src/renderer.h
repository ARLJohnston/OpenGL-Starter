#ifndef RENDERER
#define RENDERER

#include <vector.h>
#include <shader.h>
#include <texture.h>
#include <string.h>
#include <orthographicCamera.h>
#include <viewMatrix.h>
#include <GLFW/glfw3.h>

void rendererInit(const char* vertexShaderPath, const char* fragmentShaderPath);
void draw();
void terminate(); 
void updateCamera(GLFWwindow *window);

#endif
