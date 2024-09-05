3D Renderer Project
Overview
This project is a custom 3D renderer implemented in C using SDL2. It loads 3D models from OBJ files and renders them to the screen, demonstrating fundamental concepts of 3D computer graphics.
Features

OBJ file loading and rendering
3D to 2D projection
Multiple rendering modes:

Wireframe
Filled triangles
Filled triangles with wireframe overlay


Backface culling
Basic camera system
Real-time rotation of 3D models

Prerequisites
To build and run this project, you'll need:

A C compiler (e.g., GCC)
SDL2 library
Make (optional, for building)

Building the Project

Clone the repository:
Copy: git clone https://github.com/Boukindrach/3D_littel_Graphic-Engine.git

cd 3d-renderer

Build the project:
Copymake
If you don't have Make installed, you can compile manually:
Copygcc -o renderer main.c display.c vector.c mesh.c array.c camera.c -lSDL2 -lm


Running the Application
After building, run the application:
Copy./renderer
Controls

1: Switch to wireframe rendering mode by pressing 1
2: Switch to filled triangle rendering mode by pressing 2
3: Switch to filled triangle with wireframe overlay mode by pressing 3
C: Enable backface culling by pressing c
D: Disable backface culling by pressing d
ESC: Exit the application

Project Structure

main.c: Main application logic
display.h/c: Functions for display and rendering
vector.h/c: Vector mathematics operations
mesh.h/c: Mesh data structure and operations
array.h/c: Dynamic array implementation
camera.h/c: Camera system

Future Improvements

Texture mapping
Lighting system
More advanced camera controls
Performance optimizations for larger meshes

By Rachid Boukind
