*This project has been created as part of the 42 curriculum by jinliang*

# miniRT

## Description
`miniRT` simulates the propagation of light rays through a 3D environment to render photorealistic 2D images. Rather than relying on hardware-accelerated rasterization pipelines, miniRT calculates the path of individual light rays backwards from the camera lens through every pixel on the screen, evaluating geometry intersections, light attenuation, diffuse shading, and dynamic shadow casting.

### Goal
This project is an introduction to the beautiful world of Ray Tracing, designed to explore the fundamentals of computer graphics, 3D vector mathematics, and ray-object intersection algorithms, implementing geometry rendering, lighting, and shadows to render simple computer-generated images.

### Features
- **Geometric Primitives**: Native support  **Spheres**, **Planes**, and **Cylinders**.

- **Lighting Model**:
  Implements Phong/Lambertian shading with Ambient, Diffuse, and Specular lighting.

- **Hard Shadows**:
  Simulates realistic shadows by tracing shadow rays from intersection points toward light sources.

- **Material System**:
  Supports configurable material properties:
  - Specular coefficient
  - Shininess
  - Reflection
  - Transparency
  - Checkerboard textures

- **Interactive Camera Controls**
  - **Camera Lock Mechanism**: Input safety lock to prevent unintended camera movement.
  - **3D Translation (WASD & Directional Keys)**: Move the camera freely in 3D space.
  - **Field of View Zoom**: Smooth optical zoom via mouse scroll wheel.

- **Custom Scene Parsing**: Parse scenes dynamically from `.rt` configuration files with strict error handling.

## Instruction

### Compile the project:

```bash
make
```



### Run a scene:
Execute the program by passing a valid `.rt` scene configuration file as an argument:
```bash
./miniRT scenes/<rt_file_name>.rt
```
### Scene File Format (.rt)
A scene file describes the camera, lights, objects and optional materials.

The parser accepts optional material parameters after the required object parameters.
Optional parameters must follow the color field and are parsed from left to right.

#### Basic Structure

```text
A <ambient_ratio> <r,g,b>

C <x,y,z> <nx,ny,nz> <FOV>

L <x,y,z> <brightness> <r,g,b>

```

#### Camera
| C | \<position\>| \<orientation\> | \<FOV\> |
| :---: | :--- | :--- | :---: |
| | Camera coordinates | Normalized direction vector | Field of view in degrees |

#### Ambient Light
```text
A <ratio> <r,g,b>
```

#### Point Light
```text
L <position> <brightness> <r,g,b>
```

#### Objects
- **Sphere**
```text
sp <x,y,z> <diameter> <r,g,b> (optionals: [ks] [shininess] [reflectivity] [transparency] [ior] [checkerboard])
```
- **Plane**
```text
pl <x,y,z> <nx,ny,nz> <r,g,b> (optionals: [material parameters])
```
- **Cylinder**
```text
cy <x,y,z> <nx,ny,nz> <diameter> <height> <r,g,b> (optionals: [material parameters])
```

#### Material Parameters
Material parameters are parsed in this order:
```text
ks shininess reflectivity transparency ior checkerboard checker_size
```
| **Parameter** | **Description** |**Examples** |
| :--- | :---: | :---: |
| `ks` | Specular coefficient | 0 = no shine, 1 = glossy |
| `shininess` | Specular exponent | 32.0 = shiny, 1.0 = dull |
|`reflectivity` | Reflection intensity | 0.0 = no reflection, 1.0 = perfect mirror |
|`transparency` | Transparency amount | 0.0 = opaque, 1.0 = fully transparent |
|`ior` | Index of refraction | 1.0 = vacuum, 1.33 = water, 1.5 = glass, 2.42 = diamond |
|`checkboard` | Enable checker texture (0/1) | 0 = no checkerboard, 1 = checkerboard pattern |
|`checker_size` | Checker square size | 1.0 = 1m x 1m checkerboard squares (world units) |

- *Specular Coefficient determines the total amount of shiny light reflected off a surface.*
- *Specular Exponent dictates how "focused" or spread out the shiny reflection is. It is heavily tied to surface roughness.*

### Controls & Keybindings

🔒 By default, camera position and zoom level are **locked** to prevent accidental inputs.

Press **`Space`** : to toggle **Lock / Unlock Camera mode** 
#### 🔍 Zoom Controls
| Input | Action | Effect |
| :---: | :--- | :--- |
| **Mouse Wheel Up** | **Zoom In** | Narrows camera FOV |
| **Mouse Wheel Down** | **Zoom Out** | Widens camera FOV |

#### 🚶 Camera Movement (Translation)
| Key | Action | Description |
| :---: | :--- | :--- |
| **`W`** | **Move Forward** | Move along camera direction |
| **`S`** | **Move Backward** | Move along camera direction |
| **`A`** / **⬅️** | **Move Left** | Strafe left |
| **`D`** / **➡️** | **Move Right** | Strafe right |
| **⬆️** | **Move UP** | Strafe upwards |
| **⬇️** | **Move Down** | Strafe downwards |

**Exit**: to clean up memory and close application, press **`ESC`** or click on the ❌ on the window

### Cleaning
```bash
make clean 		# Remove object files
make fclean		# Remove object files and executable
make re			# Recompile from scratch
```

## Algorithm

### 1. Architecture & Key Data Structures
```

```

### Intersect
#### Cylinder
```
intersect_cylinder()
        |
        +------ hit_body()
        |
        +------ hit_cap()
        |
        +------ body_normal()
```


## Ray Tracing Theory

miniRT is based on the idea that an image can be generated by simulating how light rays travel through a scene.

Unlike real life, where light travels **from the light source to the eye**, ray tracing traces rays **backwards**: from the camera through each pixel into the scene. This produces the same visible result while being computationally practical.

---

#### 1. Camera Rays

For every pixel on the screen:

1. Convert the pixel position into viewport coordinates.
2. Build a ray starting from the camera origin.
3. Normalize the ray direction.

```
Camera
   |
   |\
   | \
   |  \
   |   \
 Pixels --> Rays
```

In code:

```c
ray.origin = camera.position;
ray.dir = normalize(pixel_position - camera.position);
```


#### 2. Ray-Object Intersection

Each ray is tested against every object in the scene.

The closest valid intersection is selected.

```
Camera -----> Sphere
          \
           \
            Plane
```

Each intersection stores:

- hit point
- surface normal
- distance `t`
- material

The smallest positive `t` is the visible object.

#### 3. Surface Normal

A normal is a unit vector perpendicular to the surface.

It tells us which direction the surface is facing.

Sphere:

```
          ↑ normal
          |
      •---O
```

```
normal = normalize(hit_point - sphere_center)
```

Planes already have a constant normal.

Cylinder normals are computed by projecting the hit point onto the cylinder axis and removing the axial component.


#### 4. Diffuse Lighting (Lambert)

Diffuse lighting models rough surfaces.

Only the angle between the light and the surface matters.

The brightness is

```
brightness = max(0, dot(normal, light_direction))
```

When:

- dot = 1 → fully illuminated
- dot = 0 → grazing angle
- dot < 0 → no light


#### 5. Specular Reflection (Phong)

Specular lighting creates shiny highlights.

The reflected light direction is

```
R = reflect(-L, N)
```

The viewer direction is compared against the reflected direction.

```
specular = ks * pow(max(dot(V, R), 0), shininess)
```

Higher **shininess** produces a smaller, sharper highlight.


#### 6. Shadows

To determine whether a point is illuminated, another ray is cast toward the light.

```
Light
  ▲
  │
Shadow Ray
  │
Hit Point
```

If another object is hit before reaching the light, the point is considered in shadow and receives only ambient illumination.


#### 7. Reflection (Bonus)

Reflection uses the law of reflection.


The reflected ray is

```
reflection = reflect(view_direction, normal)
```

That reflected ray is traced recursively until a maximum depth is reached.

#### 8. Rendering Pipeline

For every pixel:

```
Camera
   ↓
Generate Ray
   ↓
Intersect Scene
   ↓
Find Closest Hit
   ↓
Compute Normal
   ↓
Shadow Test
   ↓
Ambient + Diffuse + Specular
   ↓
Reflection (Bonus)
   ↓
Final Color
```

Finally, the floating-point color values `[0.0, 1.0]` are converted into 8-bit RGB values `[0, 255]` before writing them into the MiniLibX image buffer.


### Rendering Pipeline

#### 1. Ray Generation
For each pixel $(x, y)$ on the screen, a **Primary Ray** $\vec{R}(t)$ is constructed from the camera position $\vec{O}$ through the normalized viewport coordinate $(u, v)$:

$$\vec{R}(t) = \vec{O} + t \cdot \vec{D}$$

* $\vec{O}$: Camera origin vector
* $\vec{D}$: Normalized direction vector pointing to the pixel
* $t$: Distance along the ray ($t > 0$)

#### 2. Ray-Object Intersection Detection
The primary ray is tested against every geometric object in the scene to find the **closest hit point** (smallest positive distance $t$):

* **Sphere**: Solves a quadratic equation $at^2 + bt + c = 0$ using the discriminant $\Delta = b^2 - 4ac$.
* **Plane**: Solves a linear equation using the dot product between ray direction and plane normal.
* **Cylinder**: Intersects the curved infinite tube (quadratic equation in 2D projection) clamped by two cap planes.

#### 3. Shading & Shadow Rays (Phong / Lambert Model)
Once an intersection point $\mathbf{P}$ is found, the final color is calculated using the **Lambertian Diffuse Reflection** model:

1. **Ambient Light**: Base color of the object multiplied by the global ambient ratio.
2. **Diffuse Light**: Proportional to the cosine of the angle $\theta$ between the surface normal $\vec{N}$ and light vector $\vec{L}$:
   $$\text{Diffuse} = \text{Color} \times \text{Light Brightness} \times \max(0, \vec{N} \cdot \vec{L})$$
3. **Shadow Check**: A **Shadow Ray** is cast from point $\mathbf{P}$ towards the light source. If any object intersects this shadow ray before reaching the light, the point is in shadow (only ambient light is applied).

#### 4. Supersampling Antialiasing (AA) *(Optional)*
To smooth jagged edges, each pixel is divided into a $2 \times 2$ grid. Four sub-rays are cast per pixel, and their resultant colors are averaged ($25\%$ weight each) before rendering to the frame buffer.

---

## Dependencies
- Language: Pure C (42 Norminette compliant)
- Graphics Library: **MiniLibX** (42's internal simple graphics library for window handling and pixel rendering).

## Resources
### Official Documentation
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
- [Ray Tracing: The Rest of Your Life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)
- [Ray Tracer Challenge](http://raytracerchallenge.com/)


## Author
GitHub: [@jinlng](https://github.com/jinlng)