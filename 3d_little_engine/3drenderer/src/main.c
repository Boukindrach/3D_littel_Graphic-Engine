#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"
#define FBS 30
#define FRAME_TARGET_TIME (1000 / FBS)

triangle_t *triangles_to_render = NULL;
float scale_ = 500;
vector3d_t camera_position =  {.x = 0 , .y = 0, .z = -5};
bool is_running = false;
int previous_frame_time = 0;

void setup(void) {
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT);

	//load_cube_mesh_data();
	load_obj_file_data("./assets/car.obj");
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
	};
}

vector2d_t project(vector3d_t point) {
	vector2d_t projected_point = {
		.x = (scale_ * point.x) / point.z,
		.y = (scale_ * point.y) / point.z
	};
	return projected_point;

}

void update(void) {
	triangles_to_render = NULL;
	mesh.rotation.x += 0.001;
	mesh.rotation.y += 0.001;
	mesh.rotation.z += 0.001;
	
	int number_faces = array_length(mesh.faces);
	for (int i = 0; i < number_faces; i++) {
		face_t mesh_face = mesh.faces[i];
		vector3d_t face_vertices[3];
		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];
		triangle_t projected_triangle;
		for (int j = 0; j < 3; j++) {
			vector3d_t transformed_vertex = face_vertices[j];
			transformed_vertex = vector3d_rotate_x(transformed_vertex, mesh.rotation.x);
                	transformed_vertex = vector3d_rotate_y(transformed_vertex, mesh.rotation.y);
                	transformed_vertex = vector3d_rotate_z(transformed_vertex, mesh.rotation.z);
			transformed_vertex.z -= camera_position.z;
			vector2d_t projected_point = project(transformed_vertex);
			projected_point.x += (WIDTH / 2);
                        projected_point.y += (HEIGHT / 2);
			projected_triangle.points[j] = projected_point;
		};
		array_push(triangles_to_render, projected_triangle);
	};

}

void render(void) {
	int number_triangles = array_length(triangles_to_render);
	for (int i = 0; i < number_triangles; i++) {
		triangle_t triangle = triangles_to_render[i];
		draw_rectangle(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xffffff00);
		draw_rectangle(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xffffff00);
		draw_rectangle(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xffffff00);

		draw_triangle(
				triangle.points[0].x,
				triangle.points[0].y,
				triangle.points[1].x,
                                triangle.points[1].y,
				triangle.points[2].x,
                                triangle.points[2].y,
				0xFF00FF00
				);

	}
	array_free(triangles_to_render);

	render_color_buffer();
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);
}

void free_resources(void) {
	free(color_buffer);
	array_free(mesh.faces);
	array_free(mesh.vertices);
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
	free_resources();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
