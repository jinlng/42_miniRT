/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:36:47 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/03 18:02:12 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Fill quad coefficients for the cone body.
** k = radius/height = tan(half-angle)
** Returns m (dot dir,axis) and n (dot oc,axis) for height clamping.
*/
static void cone_quad(t_ray ray, t_object *obj, t_quad *q,
                        double *m, double *n)
{
    t_vec3  oc;
    t_vec3  d_perp;
    t_vec3  oc_perp;
    double  k;

    k       = obj->cone.radius / obj->cone.height;
    oc      = vec3_sub(ray.origin, obj->cone.apex);
    *m      = vec3_dot(ray.dir, obj->cone.axis);
    *n      = vec3_dot(oc, obj->cone.axis);
    d_perp  = vec3_sub(ray.dir, vec3_scale(obj->cone.axis, *m));
    oc_perp = vec3_sub(oc, vec3_scale(obj->cone.axis, *n));
    q->a    = vec3_dot(d_perp, d_perp) - k * k * (*m) * (*m);
    q->b    = 2.0 * (vec3_dot(d_perp, oc_perp) - k * k * (*m) * (*n));
    q->c    = vec3_dot(oc_perp, oc_perp) - k * k * (*n) * (*n);
}

/*
** Outward normal: normalize(perp - k²*proj*axis)
** perp = hit_point - apex - proj*axis  (radial vector at that height)
*/
static t_vec3   cone_body_normal(t_object *obj, t_vec3 point, double proj)
{
    t_vec3  perp;
    double  k;

    k    = obj->cone.radius / obj->cone.height;
    perp = vec3_sub(point,
                vec3_add(obj->cone.apex,
                    vec3_scale(obj->cone.axis, proj)));
    return (vec3_norm(
        vec3_sub(perp, vec3_scale(obj->cone.axis, k * k * proj))));
}

static int  check_cone_body(t_ray ray, t_object *obj,
                              t_hit *hit, double t, double m, double n)
{
    double  proj;
    t_vec3  outward;

    if (t < EPSILON)
        return (0);
    proj = n + t * m;
    if (proj < 0.0 || proj > obj->cone.height)
        return (0);
    hit->t      = t;
    hit->point  = ray_at(ray, t);
    hit->mat    = &obj->mat;
    outward     = cone_body_normal(obj, hit->point, proj);
    hit->front_face = vec3_dot(ray.dir, outward) < 0;
    if (hit->front_face)
        hit->normal = outward;
    else
        hit->normal = vec3_negate(outward);
    return (1);
}

static int  hit_cone_body(t_ray ray, t_object *obj, t_hit *hit)
{
    t_quad  q;
    double  m;
    double  n;

    cone_quad(ray, obj, &q, &m, &n);
    if (!quad_solve(&q))
        return (0);
    if (check_cone_body(ray, obj, hit, quad_root1(&q), m, n))
        return (1);
    return (check_cone_body(ray, obj, hit, quad_root2(&q), m, n));
}

static int  hit_cone_cap(t_ray ray, t_object *obj, t_hit *hit)
{
    t_vec3  cap_center;
    double  denom;
    double  t;
    t_vec3  point;
    t_vec3  to_hit;

    cap_center = vec3_add(obj->cone.apex,
                    vec3_scale(obj->cone.axis, obj->cone.height));
    denom = vec3_dot(ray.dir, obj->cone.axis);
    if (fabs(denom) < EPSILON)
        return (0);
    t = vec3_dot(vec3_sub(cap_center, ray.origin),
            obj->cone.axis) / denom;
    if (t < EPSILON)
        return (0);
    point  = ray_at(ray, t);
    to_hit = vec3_sub(point, cap_center);
    if (vec3_dot(to_hit, to_hit)
            > obj->cone.radius * obj->cone.radius)
        return (0);
    hit->t          = t;
    hit->point      = point;
    hit->mat        = &obj->mat;
    hit->front_face = denom < 0;
    if (denom < 0)
        hit->normal = obj->cone.axis;
    else
        hit->normal = vec3_negate(obj->cone.axis);
    return (1);
}

int intersect_cone(t_ray ray, t_object *obj, t_hit *hit)
{
    t_hit   body_hit;
    t_hit   cap_hit;
    int     got;

    got = 0;
    if (hit_cone_body(ray, obj, &body_hit))
    {
        *hit = body_hit;
        got  = 1;
    }
    if (hit_cone_cap(ray, obj, &cap_hit))
    {
        if (!got || cap_hit.t < hit->t)
        {
            *hit = cap_hit;
            got  = 1;
        }
    }
    return (got);
}