#include "matrix.h"

matrix4_t mat4_identity(void) {
	matrix4_t m = {{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}};
	return m;
}

matrix4_t mat4_scale(float sx, float sy, float sz) {
	matrix4_t m = mat4_identity();
        m.m[0][0] = sx;
        m.m[1][1] = sy;
	m.m[2][2] = sz;
        
	return m;
}
