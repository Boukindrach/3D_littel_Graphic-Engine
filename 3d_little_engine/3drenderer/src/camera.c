#include "camera.h"

// Define the global camera object with initial position and direction
camera_t camera = {
	// Camera's initial position in the world (x, y, z)
	.position = {0, 0, 0},

	// Camera's initial direction
	.direction = {0, 0, 1}

};
