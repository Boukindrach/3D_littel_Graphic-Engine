#ifndef TRAINGLE_H
#define TRAINGLE_H

#include "vector.h"

typedef struct {
	int a;
	int b;
	int c;
} face_t;

typedef struct {
        vector2d_t points[3];
} triangle_t;

#endif

