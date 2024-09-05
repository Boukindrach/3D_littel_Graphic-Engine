#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

typedef struct {
	vector3d_t position;
	vector3d_t direction;
} camera_t;

extern camera_t camera;

#endif
