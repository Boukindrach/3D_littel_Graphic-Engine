#include "mesh.h"
#include "array.h"
#include <stdio.h>
#include <string.h>

// Define the global mesh object with initial transformation
mesh_t mesh = {
	.vertices = NULL,
	.faces = NULL,
	.rotation = {0, 0, 0},
	.scale = {1.0, 1.0, 1.0},
	.translation = {0, 0, 0}

};

// Define cube vertices
vector3d_t cube_vertices[M_CUBE_VERTICES] = {
        {.x = -1, .y = -1, .z = -1}, // 1: Bottom-left-front
        {.x = -1, .y = 1, .z = -1},  // 2: Top-left-front
        {.x = 1, .y = 1, .z = -1},   // 3: Top-right-front
        {.x = 1, .y = -1, .z = -1},  // 4: Bottom-right-front
        {.x = 1, .y = 1, .z = 1},    // 5: Top-right-back
        {.x = 1, .y = -1, .z = 1},   // 6: Bottom-right-back
        {.x = -1, .y = 1, .z = 1},   // 7: Top-left-back
        {.x = -1, .y = -1, .z = 1}   // 8: Bottom-left-back

};

// Define cube faces using indices of the vertices
face_t cube_faces[M_CUBE_FACES] = {
	// front face
        {.a = 1, .b = 2, .c = 3},
        {.a = 1, .b = 3, .c = 4},
	// right face
        {.a = 4, .b = 3, .c = 5},
        {.a = 4, .b = 5, .c = 6},
	// back face
        {.a = 6, .b = 5, .c = 7},
        {.a = 6, .b = 7, .c = 8},
	// left face
        {.a = 8, .b = 7, .c = 2},
        {.a = 8, .b = 2, .c = 1},
	// top face
        {.a = 2, .b = 7, .c = 5},
        {.a = 2, .b = 5, .c = 3},
	// bottom face
        {.a = 6, .b = 8, .c = 1},
        {.a = 6, .b = 1, .c = 4}
};

// load cube mesh data into the mesh structure
void load_cube_mesh_data(void) {
	// Push all cube vertices into the mesh vertex array
	for (int i = 0; i < M_CUBE_VERTICES; i++) {
		vector3d_t cube_vertex = cube_vertices[i];
		array_push(mesh.vertices, cube_vertex);
	}

	// Push all cube faces into the mesh face array
	for (int i = 0; i < M_CUBE_FACES; i++) {
                face_t cube_face = cube_faces[i];
                array_push(mesh.faces, cube_face);
        }
}

// load the 3D model data form an OBJ file
void load_obj_file_data(char* filename) {
        FILE *file;
        file = fopen(filename, "r"); // Open the OBJ file for reading
        char line[2000]; // Buffer to hold each line of the file
	
	// Read the file line by line
        while (fgets(line, 2000, file)) {
	// Process vertex lines that starts with "v"
                if (strncmp (line, "v ", 2) == 0) {
                        vector3d_t vertex;
			//Parse the vertex coordinates from the line
                        sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
                        array_push(mesh.vertices, vertex);
                }
	// Process face line that start with "f"
                if (strncmp (line, "f ", 2) == 0) {
                        int vertex_indices[3];
                        int texture_indices[3];
                        int normal_indices[3];
			// Parse face data with vertex/texture/normal indices
                        if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                        &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                                        &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                                        &vertex_indices[2], &texture_indices[2], &normal_indices[2]) != 9) {
				// If parsing fails, print the line and skip it
				printf("%s\n", line);
				continue;
			}
			// Create a face from the parsed vertex indices
                        face_t face = {
                                .a = vertex_indices[0],
                                .b = vertex_indices[1],
                                .c = vertex_indices[2]
                        };
                        array_push(mesh.faces, face);
                }
        }
	fclose(file); // Close the file after reading
}
