#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define M_CUBE_VERTICES 8
extern vector3d_t cube_vertices[M_CUBE_VERTICES];

#define M_CUBE_FACES (6*2)
extern face_t cube_faces[M_CUBE_FACES];

typedef struct {
	vector3d_t *vertices;
	face_t *faces;
	vector3d_t rotation;

} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);

#endif
