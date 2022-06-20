#ifndef RENDERER
#define RENDERER

#include <vector.h>
#include <shader.h>
#include <texture.h>
#include <GLFW/glfw3.h>

void rendererInit(const char* vertexShaderPath, const char* fragmentShaderPath);
void data();
void draw();
void terminate(); 

#endif
