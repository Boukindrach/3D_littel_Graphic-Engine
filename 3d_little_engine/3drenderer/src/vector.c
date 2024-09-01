#include "vector.h"
#include <math.h>

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
