#include "miniRT.h"

/*
** Build the viewport basis once per render.
** We need an 'up' hint to build the right vector via cross product.
** If the camera looks straight up or down, use a different hint.
*/
t_camera_basis  build_camera_basis(t_camera *cam)
{
    t_camera_basis  b;
    t_vec3          world_up;
    t_vec3          right;
    t_vec3          up;
    double          half_h;
    double          half_w;
    double          aspect;

    /* choose world up hint — avoid parallel with fwd */
    if (fabs(cam->dir.y) < 0.99)
        world_up = vec3(0, 1, 0);
    else
        world_up = vec3(0, 0, 1);

    /* orthonormal camera basis */
    right = vec3_norm(vec3_cross(cam->dir, world_up));
    up    = vec3_norm(vec3_cross(right, cam->dir));

    /* viewport dimensions from FOV */
    half_h = tan((cam->fov * M_PI / 180.0) / 2.0);
    aspect = (double)WIDTH / (double)HEIGHT;
    half_w = aspect * half_h;

    /*
    ** lower_left = eye + fwd - half_w*right - half_h*up
    ** horizontal = 2*half_w * right
    ** vertical   = 2*half_h * up
    */
    b.origin     = cam->pos;
    b.horizontal = vec3_scale(right, 2.0 * half_w);
    b.vertical   = vec3_scale(up,    2.0 * half_h);
    b.lower_left = vec3_sub(
        vec3_sub(
            vec3_add(cam->pos, cam->dir),
            vec3_scale(right, half_w)
        ),
        vec3_scale(up, half_h)
    );
    return (b);
}

/*
** u,v are in [0,1] — bottom-left origin, right and up positive.
** We flip v so pixel (0,0) top-left maps to viewport top-left.
*/
t_ray   get_ray(t_camera_basis *b, double u, double v)
{
    t_ray   ray;
    t_vec3  target;

    target = vec3_add(
        b->lower_left,
        vec3_add(
            vec3_scale(b->horizontal, u),
            vec3_scale(b->vertical, v)
        )
    );
    ray.origin = b->origin;
    ray.dir    = vec3_norm(vec3_sub(target, b->origin));
    return (ray);
}