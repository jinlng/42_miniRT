/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:38:13 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/03 18:01:40 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Möller–Trumbore — direct linear solve, no quadratic needed.
**
** Solve: O + t*D = v0 + u*e1 + v*e2
** where e1 = v1-v0, e2 = v2-v0, u+v ≤ 1, u ≥ 0, v ≥ 0.
**
** det > 0  → ray hits front face
** det < 0  → ray hits back face (also valid, normals flip)
** det ≈ 0  → ray parallel to triangle
*/
int intersect_triangle(t_ray ray, t_object *obj, t_hit *hit)
{
    t_vec3  e1;
    t_vec3  e2;
    t_vec3  h;
    t_vec3  s;
    t_vec3  q;
    double  det;
    double  inv_det;
    double  u;
    double  v;
    double  t;

    e1      = vec3_sub(obj->triangle.v1, obj->triangle.v0);
    e2      = vec3_sub(obj->triangle.v2, obj->triangle.v0);
    h       = vec3_cross(ray.dir, e2);
    det     = vec3_dot(e1, h);
    if (fabs(det) < EPSILON)
        return (0);
    inv_det = 1.0 / det;
    s       = vec3_sub(ray.origin, obj->triangle.v0);
    u       = vec3_dot(s, h) * inv_det;
    if (u < 0.0 || u > 1.0)
        return (0);
    q       = vec3_cross(s, e1);
    v       = vec3_dot(ray.dir, q) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return (0);
    t       = vec3_dot(e2, q) * inv_det;
    if (t < EPSILON)
        return (0);
    hit->t          = t;
    hit->point      = ray_at(ray, t);
    hit->mat        = &obj->mat;
    hit->front_face = det > 0;
    if (det > 0)
        hit->normal = obj->triangle.normal;
    else
        hit->normal = vec3_negate(obj->triangle.normal);
    return (1);
}