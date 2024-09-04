#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;


bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL");
		return false;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		fprintf(stderr, "Error creating SDL window");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer");
		return false;
	}
	return true;
}

void draw_grid(uint32_t color) {
        for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                        if (y % 10 == 0 || x % 10 == 0) {
                                color_buffer [(WIDTH * y) + x] = color;
                        }
                }
        }
}


void draw_rectangle(int x, int y, int height, int width, uint32_t color) {
        for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                	int new_x = x + i;
			int new_y = y + j;
			draw_pixel(new_x, new_y, color);
                }
        }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2,uint32_t color) {
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);

}

void draw_pixel(int x, int y, uint32_t color) {
	if  (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        	color_buffer[(WIDTH * y) + x] = color;
	}
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)longest_side_length;
	float y_inc = delta_y / (float)longest_side_length;

	float current_x = x0;
        float current_y = y0;

	for (int i = 0; i <= longest_side_length; i++) {
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}

}

void render_color_buffer(void) {
        SDL_UpdateTexture(
                color_buffer_texture,
                NULL,
                color_buffer,
                (int)(WIDTH * sizeof(uint32_t))
        );
        SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
        for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                        color_buffer [(WIDTH * y) + x] = color;
                }
        }
}
