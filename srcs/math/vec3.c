/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:37:56 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:48:40 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3  vec3(double x, double y, double z)
{
    t_vec3  v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vec3  vec3_add(t_vec3 a, t_vec3 b)
{
    return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3  vec3_sub(t_vec3 a, t_vec3 b)
{
    return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3  vec3_scale(t_vec3 v, double t)
{
    return (vec3(v.x * t, v.y * t, v.z * t));
}

t_vec3  vec3_negate(t_vec3 v)
{
    return (vec3(-v.x, -v.y, -v.z));
}

double  vec3_len(t_vec3 v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3  vec3_norm(t_vec3 v)
{
    double  len;

    len = vec3_len(v);
    if (len < 1e-12)
        return (vec3(0, 0, 0));
    return (vec3_scale(v, 1.0 / len));
}

int     vec3_near_zero(t_vec3 v)
{
    return (fabs(v.x) < 1e-8 && fabs(v.y) < 1e-8 && fabs(v.z) < 1e-8);
}
