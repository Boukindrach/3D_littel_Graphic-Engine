#ifndef TRAINGLE_H
#define TRAINGLE_H

#include <stdint.h>
#include "vector.h"

typedef struct {
	int a;
	int b;
	int c;
} face_t;

typedef struct {
        vector2d_t points[3];
} triangle_t;

void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif

