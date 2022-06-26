#ifndef ORTHO
#define ORTHO

#include <matrix.h>
void setOrthoMatrix(float left, float right, float top, float bottom, float near, float far);
float* getOrthoMatrix();

#endif
