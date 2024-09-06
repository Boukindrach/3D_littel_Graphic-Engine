#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
	float m[4][4];
} matrix4_t;

matrix4_t mat4_identity(void);
matrix4_t mat4_scale(float sx, float sy, float sz);
vector4d_t matrix4_mul_vec4(matrix4_t m, vector4d_t v);


#endif
