
#include <orthographicCamera.h>

static mat4 ortho;

void setOrthoMatrix(float left, float right, float top, float bottom, float near, float far){
	ortho[0][0] = 2/(right - left);
	ortho[0][3] = -1 * ((right + left)/(right - left));

	ortho[1][1] = 2/(top - bottom);
	ortho[1][3] = -1 * ((top + bottom)/(top - bottom));

	ortho[2][2] = (-2)/(far - near);
	ortho[2][3] = -1 * ((far + near)/(far - near));

	ortho[3][3] = 1.0f;
}

float* getOrthoMatrix(){
	return (float*)&ortho;
}
