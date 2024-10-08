#include "matrix.h"

// Function to create and return an identity matrix (4x4)
matrix4_t mat4_identity(void) {
	matrix4_t m = {{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}};
	return m;
}

// Function to create a scaling matrix based on the provided scale factors (sx, sy, sz)
matrix4_t mat4_scale(float sx, float sy, float sz) {
	matrix4_t m = mat4_identity();
        m.m[0][0] = sx;
        m.m[1][1] = sy;
	m.m[2][2] = sz;
	return m;
}

// Function to multiply a 4x4 matrix (m) by a 4D vector (v)
vector4d_t matrix4_mul_vec4(matrix4_t m, vector4d_t v) {
	vector4d_t result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return result;
}
