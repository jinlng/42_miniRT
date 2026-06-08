*This project has been created as part of the 42 curriculum by jinliang*

# miniRT

## Description
A minimal Ray Tracing engine built from scratch in C. This project is part of the 42 school curriculum, designed to explore the fundamentals of computer graphics, 3D vector mathematics, and ray-object intersection algorithms.

### Goal
This project is an introduction to the beautiful world of Ray Tracing， implementing geometry rendering, lighting, and shadows to render simple computer-generated images.

### Features
- Geometric Primitives: Accurately renders Spheres, Planes, and Cylinders.

- Lighting Model: Implements basic Phong/Lambertian shading, featuring Ambient and Diffuse lighting.

- Hard Shadows: Simulates realistic shadows by tracing rays from intersection points back to light sources.

- Camera System: Configurable camera position, orientation vector, and Field of View (FOV).

- Scene Parser: Reads and validates custom .rt files to dynamically set up the 3D environment.

## Instruction

#### Compile the project:

```bash
make
```

#### Run a scene
Execute the program by passing a valid `.rt` scene configuration file as an argument:
```bash
./miniRT scenes/multi_objects.rt
```

#### Cleaning
```bash
make clean 		# Remove object files
make fclean		# Remove object files and executable
make re			# Recompile from scratch
```
### Dependencies
- Language: Pure C (Strictly compliant with the 42 Norminette).
- Graphics Library: **MiniLibX** (42's internal simple graphics library for window handling and pixel rendering).

## Resources


## Author
GitHub: [@jinlng](https://github.com/jinlng)