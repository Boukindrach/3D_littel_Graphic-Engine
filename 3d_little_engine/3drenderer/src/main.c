#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"

const int POINT_NUMBERS = 6 * 6 * 6;
vector3d_t cube_points[POINT_NUMBERS];
vector2d_t projected_points[POINT_NUMBERS];
bool is_running = false;

void setup(void) {
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT);

	int count_point = 0;
	for (float x = -1; x <= 1; x += 0.15) {
		for (float y = -1; y <= 1; y += 0.15) {
			for (float z = -1; z <= 1; z += 0.15) {
				vector3d_t new_point = {.x = x, .y = y, .z = z};
				cube_points[count_point++] = new_point;
			}
		}
	}
}

void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;
	}
}

vector2d_t project(vector3d_t point) {
	vector2d_t projected_point = {
		.x = point.x,
		.y = point.y,
	};
	return projected_point;

}

void update(void) {
	for (int i = 0; i < POINT_NUMBERS; i++) {
		vector3d_t point = cube_points[i];
		vector2d_t projected_point = project(point);
		projected_points[i] = projected_point;
	}

}

void render(void) {
	//draw_grid(0xFFFFFFFF);
	//draw_rectangle(0xFFFF0000);
	draw_pixel(300, 400, 0x00AA0000);
	render_color_buffer();
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);
}


int main(void)
{
	is_running = initialize_window();
	
	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
