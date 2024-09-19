#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"
#include "camera.h"
#include "matrix.h"

// Constants
#define FBS 30
#define FRAME_TARGET_TIME (1000 / FBS)

// Enumerations for rendering options
enum  cull_method {
        CULL_NONE,
        CULL_BACKFACE
} cull_method;

enum render_method {
        RENDER_WIRE,
        RENDER_FILL_TRIANGLE,
        RENDER_FILL_TRIANGLE_WIRE
} render_method;

// Global variables
triangle_t *triangles_to_render = NULL;
float scale_ = 200;
bool is_running = false;
int previous_frame_time = 0;


// Initialize the renderer
void setup(void) {
	render_method = RENDER_FILL_TRIANGLE;
        cull_method = CULL_BACKFACE;
	
	// Allocate the color buffer and create the SDL texture
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT);
	
	// load the 3d model
	//load_cube_mesh_data();
	load_obj_file_data("./assets/Building.obj");
}

// Handle user input
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
			if (event.key.keysym.sym == SDLK_1)
                                render_method = RENDER_WIRE;
			if (event.key.keysym.sym == SDLK_2)
                                render_method = RENDER_FILL_TRIANGLE;
			if (event.key.keysym.sym == SDLK_3)
                                render_method = RENDER_FILL_TRIANGLE_WIRE;
			if (event.key.keysym.sym == SDLK_c)
                                cull_method = CULL_BACKFACE;
			if (event.key.keysym.sym == SDLK_d)
                                cull_method = CULL_NONE;
                        break;
	};
}

// Project a 3D point to 2D space
vector2d_t project(vector3d_t point) {
	vector2d_t projected_point = {
		.x = (scale_ * point.x) / point.z,
		.y = -(scale_ * point.y) / point.z
	};
	return projected_point;

}

// Update the scene
void update(void) {
	triangles_to_render = NULL;

	// Update mesh rotation
	mesh.rotation.x += 0.00;
	mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.00;
	mesh.scale.x += 0.002;
	mesh.scale.y += 0.001;
	
	// Create a scale transformation matrix
	matrix4_t scale_matrix = mat4_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
	
	// Loop through all mesh faces
	int number_faces = array_length(mesh.faces);
	for (int i = 0; i < number_faces; i++) {
		face_t mesh_face = mesh.faces[i];
		vector3d_t face_vertices[3];

		// Get the vertices for each face
		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];

		triangle_t projected_triangle;
		vector3d_t transformed_vertices[3];

		// Transform vertices
		for (int j = 0; j < 3; j++) {
			vector4d_t transformed_vertex = vector4d_form_vec3(face_vertices[j]);
			transformed_vertex = matrix4_mul_vec4(scale_matrix, transformed_vertex);
			transformed_vertex.z += 5;
			transformed_vertices[j] = vector3d_form_vec4(transformed_vertex);
		}

		// Perform backface culling
		if (cull_method == CULL_BACKFACE) {
			vector3d_t vector_a = transformed_vertices[0];
			vector3d_t vector_b = transformed_vertices[1];
			vector3d_t vector_c = transformed_vertices[2];

			// Calculate the edge vectors of the triangle
			vector3d_t vector_ab = vector3d_sub(vector_b, vector_a);
			vector3d_t vector_ac = vector3d_sub(vector_c, vector_a);

			// Compute the normal using the corss product
			vector3d_t normal = vector3d_cross(vector_ab, vector_ac);
			
			// Normalize the vectors
			vector3d_normalize(&vector_ab);
			vector3d_normalize(&vector_ac);
			vector3d_normalize(&normal);

			vector3d_t origin = {0, 0, 0};

			// Calculate the ray from the camera to the triangle
			vector3d_t camera_ray = vector3d_sub(origin, vector_a);
			
			float aline_camera = vector3d_dot(normal, camera_ray);
			if (aline_camera < 0) {
				continue;
			}
		}

		// Project each transformed vertex into 2D space and store in the triangle
		for (int j = 0; j < 3; j++) {
			vector2d_t projected_point = project(transformed_vertices[j]);
			projected_point.x += (WIDTH / 2);  // Adjust x-position for the screen center
                        projected_point.y += (HEIGHT / 1.75); // Adjust y-position for the screen ce
nter
			projected_triangle.points[j] = projected_point;
		};
		// Push the projected triangle into the render queue
		array_push(triangles_to_render, projected_triangle);
	};

}

// Render the traingles to the screen
void render(void) {
	int number_triangles = array_length(triangles_to_render);

	// Loop through each triangle and render it
	for (int i = 0; i < number_triangles; i++) {
		triangle_t triangle = triangles_to_render[i];
		// If the render method includes filling the triangle, draw the filled triangle
		if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE) {
			draw_filled_triangle(
				triangle.points[0].x, triangle.points[0].y,
                		triangle.points[1].x, triangle.points[1].y,
                		triangle.points[2].x, triangle.points[2].y,
				0xffffFFFF // Color value for the triangle fill
					);
		}
		
		// If the render method includes wireframe the rendering, draw the triangle wireframe
		if (render_method == RENDER_WIRE || render_method == RENDER_FILL_TRIANGLE_WIRE) {
			draw_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				0x99000009 // Color value for the wireframe
				);
		}
	}

	// Clean up and present the rendered frame
	array_free(triangles_to_render);
	render_color_buffer();
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);
}

// Free allocated resources
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
