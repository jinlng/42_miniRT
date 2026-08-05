/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:01:10 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/03 18:01:37 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	hit_object(t_ray ray, t_object *obj, t_hit *tmp)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj, tmp));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, obj, tmp));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj, tmp));
	if (obj->type == OBJ_CONE)
		return (intersect_cone(ray, obj, tmp));
	if (obj->type == OBJ_TRIANGLE)
		return (intersect_triangle(ray, obj, tmp));
	return (0);
}

int	intersect_scene(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_object	*obj;
	t_hit		tmp;
	int			hit_anything;
	double		closest;

	hit_anything = 0;
	closest = 1e15;
	obj = scene->objects;
	while (obj)
	{
		tmp.t = closest;
		if (hit_object(ray, obj, &tmp) && tmp.t < closest)
		{
			closest = tmp.t;
			*hit = tmp;
			hit_anything = 1;
		}
		obj = obj->next;
	}
	return (hit_anything);
}
