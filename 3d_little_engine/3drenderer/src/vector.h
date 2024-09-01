#ifndef VECTOR_H
#define VECTOR_H


typedef struct {

	float x;
	float y;
} vector2d_t;

typedef struct {

	float x;
	float y;
	float z;
} vector3d_t;

vector3d_t vector3d_rotate_x(vector3d_t v, float angle);
vector3d_t vector3d_rotate_y(vector3d_t v, float angle);
vector3d_t vector3d_rotate_z(vector3d_t v, float angle);

#endif
