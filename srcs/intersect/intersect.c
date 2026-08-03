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

static int	handle_sphere(t_ray ray, t_object *obj, t_hit *hit, double *closest)
{
	t_hit	tmp;

	tmp.t = *closest;
	if (intersect_sphere(ray, obj, &tmp) && tmp.t < *closest)
	{
		*closest = tmp.t;
		*hit = tmp;
		return (1);
	}
	return (0);
}

static int	handle_plane(t_ray ray, t_object *obj, t_hit *hit, double *closest)
{
	t_hit	tmp;

	tmp.t = *closest;
	if (intersect_plane(ray, obj, &tmp) && tmp.t < *closest)
	{
		*closest = tmp.t;
		*hit = tmp;
		return (1);
	}
	return (0);
}

static int	handle_cylinder(t_ray ray, t_object *obj, t_hit *hit,
		double *closest)
{
	t_hit	tmp;

	tmp.t = *closest;
	if (intersect_cylinder(ray, obj, &tmp) && tmp.t < *closest)
	{
		*closest = tmp.t;
		*hit = tmp;
		return (1);
	}
	return (0);
}

static int	handle_cone(t_ray ray, t_object *obj, t_hit *hit,
		double *closest)
{
	t_hit	tmp;

	tmp.t = *closest;
	if (intersect_cone(ray, obj, &tmp) && tmp.t < *closest)
    {
        *closest = tmp.t;
        *hit    = tmp;
        return (1);
    }
	return (0);
}

static int	handle_triangle(t_ray ray, t_object *obj, t_hit *hit,
		double *closest)
{
	t_hit	tmp;

	tmp.t = *closest;
	if (intersect_triangle(ray, obj, &tmp) && tmp.t < *closest)
    {
	    *closest = tmp.t;
        *hit    = tmp;
        return (1);
    }
	return (0);
}

int	intersect_scene(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_object	*obj;
	int			hit_anything;
	double		closest;

	hit_anything = 0;
	closest = 1e15;
	obj = scene->objects;
	while (obj)
	{
		if (obj->type == OBJ_SPHERE)
			hit_anything |= handle_sphere(ray, obj, hit, &closest);
		else if (obj->type == OBJ_PLANE)
			hit_anything |= handle_plane(ray, obj, hit, &closest);
		else if (obj->type == OBJ_CYLINDER)
			hit_anything |= handle_cylinder(ray, obj, hit, &closest);
		else if (obj->type == OBJ_CONE)
			hit_anything |= handle_cone(ray, obj, hit, &closest);
		else if (obj->type == OBJ_TRIANGLE)
			hit_anything |= handle_triangle(ray, obj, hit, &closest);
		obj = obj->next;
	}
	return (hit_anything);
}
