/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:00:55 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 23:48:02 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_plane(t_ray ray, t_object *obj, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	to_plane;

	denom = vec3_dot(ray.dir, obj->plane.normal);
	if (fabs(denom) < EPSILON)
		return (0);
	to_plane = vec3_sub(obj->plane.point, ray.origin);
	t = vec3_dot(to_plane, obj->plane.normal) / denom;
	if (t < EPSILON)
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->mat = &obj->mat;
	if (denom < 0)
		hit->normal = obj->plane.normal;
	else
		hit->normal = vec3_negate(obj->plane.normal);
	hit->front_face = (denom < 0);
	return (1);
}
