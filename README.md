
# Ray Tracer with BVH Acceleration and OBJ File Support

This is a custom ray tracer that is optimized with Bounding Volume Hierarchy (BVH) and loads OBJs to render more complex 3D models. It implements multiple materials, such as dielectric and metal, and also includes imported materials associated with OBJ models to create 3D scenes with realistic lighting and reflection.


## Features

- BVH-acceleration for faster ray-object intersection and overall rendering time
- Supports OBJ loading and their respective materials
- Adjustable camera position, field of view, depth, blur, defocus angle, and aspect ratio


## Tech Stack

**Language:** C++17


## Dependencies

This project does not have any dependencies that need to be downloaded externally! All libraries are included in headers found in the source file.

## Installation and running

**Note** You will need to open build.py to edit configurations to fit your system. 
1. Clone the repository:
```bash
  git clone <project-url>
  cd project
  ```
2. Install dependencies
3. Build project
```bash
  python3 build.py
  ```
4. ...and run!
```bash
  ./proj -> image.ppm 
  ```
Currently, this will create the batarang shown in this README - if you would like to try with a different OBJ, just add it into the directory and change the line of code in main.cpp.
## Acknowledgements

 - [Ray Tracing in One Weekend series](https://raytracing.github.io/)
 - [TinyOBJLoader](https://github.com/tinyobjloader/tinyobjloader)

