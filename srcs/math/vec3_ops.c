/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:38:21 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:48:43 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double  vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3  vec3_cross(t_vec3 a, t_vec3 b)
{
    return (vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    ));
}

/*
** Reflect v around normal n.
** Used later for specular (bonus) — stubbed now, costs nothing.
** Formula: v - 2*dot(v,n)*n
*/
t_vec3  vec3_reflect(t_vec3 v, t_vec3 n)
{
    return (vec3_sub(v, vec3_scale(n, 2.0 * vec3_dot(v, n))));
}

/*
** Point along ray at distance t: P = origin + t*dir
*/
t_vec3  ray_at(t_ray ray, double t)
{
    return (vec3_add(ray.origin, vec3_scale(ray.dir, t)));
}
