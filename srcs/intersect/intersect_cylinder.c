#include "miniRT.h"

/*
** Outward normal for a point on the cylinder body.
** Project hit point onto axis, subtract that component.
*/
static t_vec3   body_normal(t_object *obj, t_vec3 point)
{
    double  proj;
    t_vec3  radial;

    proj   = vec3_dot(vec3_sub(point, obj->cylinder.center),
                      obj->cylinder.axis);
    radial = vec3_sub(point,
                vec3_add(obj->cylinder.center,
                    vec3_scale(obj->cylinder.axis, proj)));
    return (vec3_norm(radial));
}

/*
** Try to hit one end cap.
** cap_center = cylinder.center ± axis*(height/2)
** cap_normal = ±axis (must face the incoming ray)
** Returns 1 and fills hit if the ray hits inside the cap disk.
*/
static int  hit_cap(t_ray ray, t_object *obj, t_vec3 cap_center,
                    t_vec3 cap_normal, t_hit *hit)
{
    double  denom;
    double  t;
    t_vec3  to_cap;
    t_vec3  point;
    t_vec3  to_hit;

    denom = vec3_dot(ray.dir, cap_normal);
    if (fabs(denom) < EPSILON)
        return (0);
    to_cap = vec3_sub(cap_center, ray.origin);
    t      = vec3_dot(to_cap, cap_normal) / denom;
    if (t < EPSILON)
        return (0);
    point  = ray_at(ray, t);
    to_hit = vec3_sub(point, cap_center);
    /* point must be inside the cap disk */
    if (vec3_dot(to_hit, to_hit) > obj->cylinder.radius * obj->cylinder.radius)
        return (0);
    hit->t          = t;
    hit->point      = point;
    hit->color      = obj->color;
    /* normal faces away from the ray */
    if (denom < 0)
        hit->normal = cap_normal;
    else
        hit->normal = vec3_negate(cap_normal);
    hit->front_face = (denom < 0);
    return (1);
}

/*
** Cylinder body intersection.
** Projects ray and oc onto the plane perpendicular to the axis,
** solves 2D circle quadratic, clamps each root to the height range.
*/
static int  hit_body(t_ray ray, t_object *obj, t_hit *hit)
{
    t_vec3  oc;
    t_vec3  d;
    t_vec3  f;
    double  a;
    double  b;
    double  c;
    double  disc;
    double  sq;
    double  t;
    double  proj;
    int     found;

    oc    = vec3_sub(ray.origin, obj->cylinder.center);
    d     = vec3_sub(ray.dir,
                vec3_scale(obj->cylinder.axis,
                    vec3_dot(ray.dir, obj->cylinder.axis)));
    f     = vec3_sub(oc,
                vec3_scale(obj->cylinder.axis,
                    vec3_dot(oc, obj->cylinder.axis)));
    a     = vec3_dot(d, d);
    if (fabs(a) < EPSILON)
        return (0);
    b     = 2.0 * vec3_dot(d, f);
    c     = vec3_dot(f, f)
                - obj->cylinder.radius * obj->cylinder.radius;
    disc  = b * b - 4.0 * a * c;
    if (disc < 0)
        return (0);
    sq    = sqrt(disc);
    found = 0;
    /* try smaller root */
    t     = (-b - sq) / (2.0 * a);
    if (t >= EPSILON)
    {
        proj = vec3_dot(
            vec3_sub(ray_at(ray, t), obj->cylinder.center),
            obj->cylinder.axis);
        if (proj >= -obj->cylinder.height / 2.0
            && proj <= obj->cylinder.height / 2.0)
        {
            hit->t      = t;
            hit->point  = ray_at(ray, t);
            hit->normal = body_normal(obj, hit->point);
            hit->color  = obj->color;
            hit->front_face = (vec3_dot(ray.dir, hit->normal) < 0);
            if (!hit->front_face)
                hit->normal = vec3_negate(hit->normal);
            found = 1;
        }
    }
    if (found)
        return (1);
    /* try larger root (ray inside cylinder) */
    t = (-b + sq) / (2.0 * a);
    if (t < EPSILON)
        return (0);
    proj = vec3_dot(
        vec3_sub(ray_at(ray, t), obj->cylinder.center),
        obj->cylinder.axis);
    if (proj < -obj->cylinder.height / 2.0
        || proj > obj->cylinder.height / 2.0)
        return (0);
    hit->t      = t;
    hit->point  = ray_at(ray, t);
    hit->normal = body_normal(obj, hit->point);
    hit->color  = obj->color;
    hit->front_face = (vec3_dot(ray.dir, hit->normal) < 0);
    if (!hit->front_face)
        hit->normal = vec3_negate(hit->normal);
    return (1);
}

/*
** Full cylinder: test body and both caps, return closest valid hit.
*/
int intersect_cylinder(t_ray ray, t_object *obj, t_hit *hit)
{
    t_hit   body_hit;
    t_hit   cap_hit;
    t_vec3  top_center;
    t_vec3  bot_center;
    int     got_body;
    int     got_cap;
    double  best;

    best       = 1e15;
    got_body   = 0;
    got_cap    = 0;
    top_center = vec3_add(obj->cylinder.center,
                    vec3_scale(obj->cylinder.axis,
                        obj->cylinder.height / 2.0));
    bot_center = vec3_sub(obj->cylinder.center,
                    vec3_scale(obj->cylinder.axis,
                        obj->cylinder.height / 2.0));
    if (hit_body(ray, obj, &body_hit) && body_hit.t < best)
    {
        best     = body_hit.t;
        *hit     = body_hit;
        got_body = 1;
    }
    if (hit_cap(ray, obj, top_center, obj->cylinder.axis, &cap_hit)
        && cap_hit.t < best)
    {
        best    = cap_hit.t;
        *hit    = cap_hit;
        got_cap = 1;
    }
    if (hit_cap(ray, obj, bot_center,
            vec3_negate(obj->cylinder.axis), &cap_hit)
        && cap_hit.t < best)
    {
        *hit    = cap_hit;
        got_cap = 1;
    }
    return (got_body || got_cap);
}