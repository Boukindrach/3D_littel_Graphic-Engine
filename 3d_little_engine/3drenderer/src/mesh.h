#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define M_CUBE_VERTICES 8
extern vector3d_t cube_vertices[M_CUBE_VERTICES];

#define M_CUBE_FACES (6*2) // 6 cube faces, 2 triangles per face.
extern face_t cube_faces[M_CUBE_FACES];

/////////////////////////////////////////////////////////////////////////////
// Define a struct for dynamic size meshes, with array of vertices and faces
/////////////////////////////////////////////////////////////////////////////

typedef struct {
	vector3d_t *vertices; // dynamic array of vertices
	face_t *faces;	// dynamic array of faces
	vector3d_t rotation; // rotation with x, y and z values
	vector3d_t scale;	// scale with x, y and z values
	vector3d_t translation;	// translation with x, y and z values

} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void load_obj_file_data(char* filename);
#endif
