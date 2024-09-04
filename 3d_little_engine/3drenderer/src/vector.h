#ifndef VECTOR_H
#define VECTOR_H


typedef struct {

	float x, y;
} vector2d_t;

typedef struct {

	float x, y, z;
} vector3d_t;

float vector2d_length(vector3d_t v);

float vector3d_length(vector3d_t v);

vector3d_t vector3d_rotate_x(vector3d_t v, float angle);
vector3d_t vector3d_rotate_y(vector3d_t v, float angle);
vector3d_t vector3d_rotate_z(vector3d_t v, float angle);

#endif
