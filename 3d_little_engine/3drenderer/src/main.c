#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
#define POINT_NUMBERS (9 * 9 * 9)
vector3d_t cube_points[POINT_NUMBERS];
vector2d_t projected_points[POINT_NUMBERS];
float scale_ = 500;
vector3d_t camera_position =  {.x = 0 , .y = 0, .z = -5};
vector3d_t cube_rotation = {.x = 0 , .y = 0, .z =  0};
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
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
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
		.x = (scale_ * point.x) / point.z,
		.y = (scale_ * point.y) / point.z
	};
	return projected_point;

}

void update(void) {
	cube_rotation.y += 0.1;
	for (int i = 0; i < POINT_NUMBERS; i++) {
		vector3d_t point = cube_points[i];
		vector3d_t transformed_point = vector3d_rotate_y(point, cube_rotation.y);
		transformed_point.z -= camera_position.z;
		vector2d_t projected_point = project(transformed_point);
		projected_points[i] = projected_point;
	}

}

void render(void) {
	//draw_grid(0xFFFFFFFF);
	//draw_rectangle(0xFFFF0000);
	//draw_pixel(300, 400, 0x00AA0000);
	for (int i = 0; i <= POINT_NUMBERS; i++) {
		vector2d_t projected_point = projected_points[i];
		draw_rectangle(projected_point.x + (WIDTH / 2),
			       	projected_point.y + (HEIGHT / 2),
				4,
				4,
				0xffff0000);
	}
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
