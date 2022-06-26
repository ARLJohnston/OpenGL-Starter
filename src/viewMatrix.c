#include <viewMatrix.h>

static mat4 view = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
};

void setViewMatrix(float x, float y){
	view[3][0] = x;
	view[3][1] = y;
}

float* getViewMatrix(){
	return (float*)&view;
}
