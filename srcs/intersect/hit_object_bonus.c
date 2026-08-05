/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:00:00 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 10:00:00 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	hit_object(t_ray ray, t_object *obj, t_hit *tmp)
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
