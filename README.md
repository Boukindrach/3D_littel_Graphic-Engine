
# Little 3d graphic engine

A lightweight 3D graphics engine designed to load and visualize OBJ files, providing a basic representation of 3D models similar to Blender. This engine allows users to render and explore the properties of 3D objects in real-time, offering a simple yet effective way to interact with OBJ geometry.


## Installation

```bash
  git clone https://github.com/Boukindrach/3D_littel_Graphic-Engine.git
cd 3D_littel_Graphic-Engine
```
you will need to install SDL2 to run the program:
```
  sudo apt-get install libsdl2-dev
```
    
## Usage

Running the engine: After successful compilation, you can run the engine with the following command:

```bash
./3D_littel_Graphic-Engine/renderer
```

if you have an obj file, upload it the assets folder and got the the main.c:
line 51, you will see something like:

    ```load_obj_file_data("./assets/Building.obj");```
replace the Building.obj with the name of you OBJ file.
## Authors

Rachid Boukind
- [on Github](https://www.github.com/Boukindrach)
- [on Linkedin](https://www.linkedin.com/in/rachid-boukind/)

