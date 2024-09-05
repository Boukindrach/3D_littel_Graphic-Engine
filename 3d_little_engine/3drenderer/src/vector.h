#ifndef VECTOR_H
#define VECTOR_H


typedef struct {

	float x, y;
} vector2d_t;

typedef struct {

	float x, y, z;
} vector3d_t;

float vector2d_length(vector2d_t v);
vector2d_t vector2d_add(vector2d_t a, vector2d_t b);
vector2d_t vector2d_sub(vector2d_t a, vector2d_t b);
vector2d_t vector2d_mul(vector2d_t v, float factor);
vector2d_t vector2d_div(vector2d_t v, float factor);
float vector2d_dot(vector2d_t a, vector2d_t b);
void vector2d_normalize(vector2d_t *v);

float vector3d_length(vector3d_t v);
vector3d_t vector3d_add(vector3d_t a, vector3d_t b);
vector3d_t vector3d_sub(vector3d_t a, vector3d_t b);
vector3d_t vector3d_mul(vector3d_t v, float factor);
vector3d_t vector3d_div(vector3d_t v, float factor);
vector3d_t vector3d_cross(vector3d_t a, vector3d_t b);
float vector3d_dot(vector3d_t a, vector3d_t b);
void vector3d_normalize(vector3d_t *v);

vector3d_t vector3d_rotate_x(vector3d_t v, float angle);
vector3d_t vector3d_rotate_y(vector3d_t v, float angle);
vector3d_t vector3d_rotate_z(vector3d_t v, float angle);

#endif
