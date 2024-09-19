#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

// Define the camera structure
typedef struct {
	vector3d_t position;
	vector3d_t direction;
} camera_t;

// Declare the camera object as an extrenal variable
extern camera_t camera;

#endif
