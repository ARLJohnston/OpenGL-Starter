#ifndef RENDERER
#define RENDERER

#include <vector.h>
#include <matrix.h>
#include <orthographicCamera.h>
#include <viewMatrix.h>
#include <shader.h>
#include <texture.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdlib.h>

void setMat4(const char* varName, float* matrix);

struct Renderer;
struct Renderer* rendererInit(int maxQuadsPerBatch);
void rendererShaderInit(struct Renderer *renderer, const char* vertexShaderPath, const char* fragmentShaderPath);
void rendererDrawQuadColour(struct Renderer *renderer, vec2 position, vec2 size, vec4 colour);
void rendererDrawQuadTexture(struct Renderer *renderer, vec2 position, vec2 size, unsigned int textureID);
void rendererFlush(struct Renderer* renderer);
void rendererClear();
void rendererTerminate();
#endif
