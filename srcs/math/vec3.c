/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:37:56 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/15 15:35:59 by jinliang         ###   ########.fr       */
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
