#ifndef RENDERER
#define RENDERER

#include <vector.h>
#include <shader.h>
#include <texture.h>
#include <string.h>
#include <orthographicCamera.h>
#include <viewMatrix.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

void updateCamera(GLFWwindow *window);
void updateZoom(GLFWwindow *window,double xoffset, double yoffset);

void renderer_init();
void renderer_shader_init(const char* vertexShaderPath, const char* fragmentShaderPath);
void renderer_terminate();
void renderer_begin_batch();
void renderer_end_batch();
void renderer_flush();
void renderer_draw_quad_colour(vec2 position, vec2 size, vec4 colour);
void renderer_draw_quad_texture(vec2 position, vec2 size, float textureindex);


#endif
