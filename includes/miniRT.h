#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <mlx.h>

# define EPSILON 1e-6
# define WIDTH   800
# define HEIGHT  600

/* ── Primitives ───────────────────────────────────────────────── */
typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}   t_vec3;

typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  dir;
}   t_ray;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

/* ── Scene elements ───────────────────────────────────────────── */
typedef struct s_ambient
{
    double  ratio;
    t_color color;
}   t_ambient;

typedef struct s_camera
{
    t_vec3  pos;
    t_vec3  dir;
    double  fov;
}   t_camera;

typedef struct s_light
{
    t_vec3          pos;
    double          brightness;
    t_color         color;
    struct s_light  *next;
}   t_light;

/* ── Objects ──────────────────────────────────────────────────── */
typedef struct s_sphere
{
    t_vec3  center;
    double  radius;
}   t_sphere;

typedef struct s_plane
{
    t_vec3  point;
    t_vec3  normal;
}   t_plane;

typedef struct s_cylinder
{
    t_vec3  center;
    t_vec3  axis;
    double  radius;
    double  height;
}   t_cylinder;

typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER,
}   t_obj_type;

typedef struct s_object
{
    t_obj_type      type;
    union {
        t_sphere    sphere;
        t_plane     plane;
        t_cylinder  cylinder;
    };
    t_color         color;
    struct s_object *next;
}   t_object;

/* ── Scene ────────────────────────────────────────────────────── */
typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     *lights;
    t_object    *objects;
    int         has_ambient;
    int         has_camera;
    int         has_light;
}   t_scene;

/* ── MLX ──────────────────────────────────────────────────────── */
typedef struct s_mlx
{
    void    *ptr;       /* mlx instance          */
    void    *win;       /* window handle         */
    void    *img;       /* image buffer          */
    char    *addr;      /* raw pixel data        */
    int     bpp;        /* bits per pixel        */
    int     line_len;   /* bytes per image row   */
    int     endian;     /* byte order            */
}   t_mlx;

/* ── App — owns everything ────────────────────────────────────── */
typedef struct s_app
{
    t_mlx   mlx;
    t_scene scene;
}   t_app;

/* ── Camera & render ──────────────────────────────────────────── */
typedef struct s_camera_basis
{
    t_vec3  origin;
    t_vec3  horizontal;   /* full width vector along viewport   */
    t_vec3  vertical;     /* full height vector along viewport  */
    t_vec3  lower_left;   /* world-space bottom-left of viewport */
}   t_camera_basis;

/* ── Hit record ───────────────────────────────────────────────── */
typedef struct s_hit
{
    double      t;          /* distance along ray          */
    t_vec3      point;      /* world-space hit position    */
    t_vec3      normal;     /* outward unit normal         */
    t_color     color;      /* object color at hit         */
    int         front_face; /* 1 if ray hits outside       */
}   t_hit;





/* ── vec3 ─────────────────────────────────────────────────────── */
t_vec3  vec3(double x, double y, double z);
t_vec3  vec3_add(t_vec3 a, t_vec3 b);
t_vec3  vec3_sub(t_vec3 a, t_vec3 b);
t_vec3  vec3_scale(t_vec3 v, double t);
t_vec3  vec3_negate(t_vec3 v);
double  vec3_dot(t_vec3 a, t_vec3 b);
t_vec3  vec3_cross(t_vec3 a, t_vec3 b);
double  vec3_len(t_vec3 v);
t_vec3  vec3_norm(t_vec3 v);
t_vec3  vec3_reflect(t_vec3 v, t_vec3 n);
int     vec3_near_zero(t_vec3 v);
t_vec3  ray_at(t_ray ray, double t);

/* ── Parser ───────────────────────────────────────────────────── */
void    parse_scene(const char *file, t_scene *scene);
void    parse_ambient(char **tokens, t_scene *scene);
void    parse_camera(char **tokens, t_scene *scene);
void    parse_light(char **tokens, t_scene *scene);
void    parse_sphere(char **tokens, t_scene *scene);
void    parse_plane(char **tokens, t_scene *scene);
void    parse_cylinder(char **tokens, t_scene *scene);

/* ── Parse utils ──────────────────────────────────────────────── */
double  parse_double(const char *s);
t_color parse_color(const char *s);
t_vec3  parse_vec3(const char *s);
t_vec3  parse_normal(const char *s);
char    **split_line(const char *line);
void    free_tokens(char **tokens);
int     token_count(char **tokens);
void    error_exit(const char *msg);

/* ── Window ───────────────────────────────────────────────────── */
void    mlx_setup(t_app *app);
void    mlx_put_pixel(t_mlx *mlx, int x, int y, t_color color);
// int     key_handler(int keycode, t_app *app);
int key_handler(int keycode, void *param);
int     close_handler(t_app *app);
void    render_test(t_app *app);

/* ── Camera & render ──────────────────────────────────────────── */
t_camera_basis  build_camera_basis(t_camera *cam);
t_ray           get_ray(t_camera_basis *basis, double u, double v);
// t_color         ray_color(t_ray ray);
t_color         ray_color(t_ray ray, t_scene *scene);
void            render(t_app *app);



/* ── Intersect prototypes ─────────────────────────────────────── */
int     intersect_sphere(t_ray ray, t_object *obj, t_hit *hit);
int     intersect_scene(t_ray ray, t_scene *scene, t_hit *hit);

/* ── Shading prototypes ───────────────────────────────────────── */
t_color shade(t_hit *hit, t_scene *scene, t_ray ray);
t_color color_scale(t_color c, double t);
t_color color_add(t_color a, t_color b);
t_color color_clamp(t_color c);
t_color color_multiply(t_color a, t_color b);

int     intersect_plane(t_ray ray, t_object *obj, t_hit *hit);
int     intersect_cylinder(t_ray ray, t_object *obj, t_hit *hit);

#endif