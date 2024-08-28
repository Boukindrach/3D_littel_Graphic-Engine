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


void draw_rectangle(uint32_t color) {
        for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                        if ((y < 400 && y > 100) && (x < 500 && x > 300)) {
                                color_buffer [(WIDTH * y) + x] = color;
                        }
                }
        }
}

void draw_pixel(int x, int y, uint32_t color) {
        color_buffer[(WIDTH * y) + x] = color;
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
