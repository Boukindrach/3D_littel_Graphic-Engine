#include "triangle.h"
#include <stdint.h>
#include "display.h"

/**
 * Swap the values of two integers.
 *
 * @a: Pointer to the first integer
 * @b: Pointer to the second integer
*/
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * Fill a flat-top triangle
 *
 * x0, y0: Coordinates of the left point
 * x1, y1: Coordinates of the right point
 * x2, y2: Coordinates of the top point
 * @color: Color to fill the triangle with
*/
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	float slope_1 = (float)(x2 - x0) / (y2 - y0);
	float slope_2 = (float)(x2 - x1) / (y2 - y1);

	float x_start = x2;
	float x_end = x2;

	for (int y = y2; y >= y0; y--) {
		draw_line(x_start, y, x_end, y,color);
		x_start -= slope_1;
		x_end -= slope_2;
	}
}

/**
 * Fill a flat-bottom triangle
 *
 * x0, y0: Coordinates of the top point
 * x1, y1: Coordinates of the bottom-left point
 * x2, y2: Coordinates of the bottom-right point
 * @color: Color to fill the triangle with
*/
void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
        float slope_1 = (float)(x1 - x0) / (y1 - y0);
        float slope_2 = (float)(x2 - x0) / (y2 - y0);

        float x_start = x0;
        float x_end = x0;

        for (int y = y0; y <= y2; y++) {
                draw_line(x_start, y, x_end, y,color);
                x_start += slope_1;
                x_end += slope_2;
        }
}

/**
 * Draw a filled triangle
 *
 * x0, y0: Coordinates of the first point
 * x1, y1: Coordinates of the second point
 * x2, y2: Coordinates of the third point
 * @color: Color to fill the triangle with
*/
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	// Sort the points so that y0 <= y1 <= y2
        if (y0 > y1) { swap(&y0, &y1); swap(&x0, &x1); }
        if (y1 > y2) { swap(&y1, &y2); swap(&x1, &x2); }
        if (y0 > y1) { swap(&y0, &y1); swap(&x0, &x1); }

	if (y1 == y2) {
		fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
	}
	else if (y0 == y1) {
		fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
	}
	else {
		// Split the traingle into a flat-bottom and flat-top traingle
		int My = y1;
		int Mx = ((float)((x2 - x0) * (y1 - y0)) / (float) (y2 - y0)) + x0;
		fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);
		fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
	}
}
