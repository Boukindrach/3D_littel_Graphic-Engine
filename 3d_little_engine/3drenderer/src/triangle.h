#ifndef TRAINGLE_H
#define TRAINGLE_H

#include <stdint.h>
#include "vector.h"

/**
 * Represents a face with three vertex indices
*/
typedef struct {
	int a; // index of the first vertex
	int b; // index of the second vertex
	int c; // index of the third vertex
} face_t;

/**
 * Represents a triangle with three 2D points
*/
typedef struct {
        vector2d_t points[3]; // array of three 2D points forming the traingle
} triangle_t;

/**
 * fill the top triangle
 *
 * x0, y0: Coordinates of the first point
 * x1, y1: Coordinates of the second point
 * x2, y2: Coordinates of the third point
 * @color: Color to fill the traingle with
*/
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

/**
 * Draw a filled triangle
 *
 * x0, y0: Coordinates of the first point
 * x1, y1: Coordinates of the second point
 * x2, y2: Coordinates of the third point
 * @color: Color to fill the traingle with
*/

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif

