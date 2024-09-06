#include "vector.h"
#include <math.h>

/////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
float vector2d_length(vector2d_t v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

vector2d_t vector2d_add(vector2d_t a, vector2d_t b) {
        vector2d_t result = {
                .x = a.x + b.x,
                .y = a.y + b.y
        };
	return result;
}

vector2d_t vector2d_sub(vector2d_t a, vector2d_t b) {
        vector2d_t result = {
                .x = a.x - b.x,
                .y = a.y - b.y
        };
	return result;
}

vector2d_t vector2d_mul(vector2d_t v, float factor) {
	vector2d_t result = {
		.x = v.x * factor,
		.y = v.y * factor,
	};
	return result;
}

vector2d_t vector2d_div(vector2d_t v, float factor) {
        vector2d_t result = {
                .x = v.x / factor,
                .y = v.y / factor,
        };
        return result;
}

float vector2d_dot(vector2d_t a, vector2d_t b) {
        return (a.x * b.x) + (a.y * b.y);
}

void vector2d_normalize(vector2d_t *v) {
	float length = sqrt(v->x * v->x + v->y * v->y);
	v->x /= length;
	v->y /= length;
}
/////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////
float vector3d_length(vector3d_t v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vector3d_t vector3d_add(vector3d_t a, vector3d_t b) {
        vector3d_t result = {
                .x = a.x + b.x,
                .y = a.y + b.y,
		.z = a.z + b.z
        };
	return result;
}

vector3d_t vector3d_sub(vector3d_t a, vector3d_t b) {
        vector3d_t result = {
                .x = a.x - b.x,
                .y = a.y - b.y,
                .z = a.z - b.z,
        };
	return result;
}

vector3d_t vector3d_mul(vector3d_t v, float factor) {
        vector3d_t result = {
                .x = v.x * factor,
                .y = v.y * factor,
		.z = v.z * factor
        };
        return result;
}

vector3d_t vector3d_div(vector3d_t v, float factor) {
        vector3d_t result = {
                .x = v.x / factor,
                .y = v.y / factor,
		.z = v.z / factor
        };
        return result;
}

vector3d_t vector3d_cross(vector3d_t a, vector3d_t b) {
	vector3d_t result = {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
	return result;

}

float vector3d_dot(vector3d_t a, vector3d_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vector3d_normalize(vector3d_t *v) {
        float length = sqrt(v->x * v->x + v->y * v->y + v->x + v->z * v->z);
        v->x /= length;
        v->y /= length;
	v->z /= length;
}

////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////
vector3d_t vector3d_rotate_x(vector3d_t v, float angle) {
	vector3d_t rotated_vector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}

vector3d_t vector3d_rotate_y(vector3d_t v, float angle) {
	vector3d_t rotated_vector = {
               	.x = v.x * cos(angle) - v.z * sin(angle),
                .y = v.y,
                .z = v.x * sin(angle) + v.z * cos(angle)
        };
        return rotated_vector;
	
}

vector3d_t vector3d_rotate_z(vector3d_t v, float angle) {
	vector3d_t rotated_vector = {
                .x = v.x * cos(angle) - v.y * sin(angle),
                .y = v.x * sin(angle) + v.y * cos(angle),
                .z = v.z
        };
        return rotated_vector;

}


vector4d_t vector4d_form_vec3(vector3d_t v) {
	vector4d_t result = (v.x, v.y, v.z, 1.0);
	return result;
}
vector3d_t vector3d_form_vec4(vector4d_t v) {
	vector3d_t result = (v.x, v.y, v.z);
        return result;
}
