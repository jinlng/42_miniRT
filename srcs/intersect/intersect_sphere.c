#include "miniRT.h"

/*
** Set the normal to always face the incoming ray.
** Store whether we hit the front or back face.
*/
static void set_face_normal(t_hit *hit, t_ray ray, t_vec3 outward_normal)
{
    hit->front_face = vec3_dot(ray.dir, outward_normal) < 0;
    if (hit->front_face)
        hit->normal = outward_normal;
    else
        hit->normal = vec3_negate(outward_normal);
}

int intersect_sphere(t_ray ray, t_object *obj, t_hit *hit)
{
    t_vec3  oc;
    double  a;
    double  b;
    double  c;
    double  disc;
    double  sqrt_disc;
    double  t;

    oc   = vec3_sub(ray.origin, obj->sphere.center);
    a    = vec3_dot(ray.dir, ray.dir);
    b    = 2.0 * vec3_dot(oc, ray.dir);
    c    = vec3_dot(oc, oc) - obj->sphere.radius * obj->sphere.radius;
    disc = b * b - 4.0 * a * c;
    if (disc < 0)
        return (0);
    sqrt_disc = sqrt(disc);
    /* try smaller root first */
    t = (-b - sqrt_disc) / (2.0 * a);
    if (t < EPSILON)
    {
        /* try larger root (ray inside sphere) */
        t = (-b + sqrt_disc) / (2.0 * a);
        if (t < EPSILON)
            return (0);
    }
    hit->t     = t;
    hit->point = ray_at(ray, t);
    hit->color = obj->color;
    set_face_normal(hit, ray,
        vec3_norm(vec3_sub(hit->point, obj->sphere.center)));
    return (1);
}