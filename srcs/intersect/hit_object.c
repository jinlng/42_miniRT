/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:00:00 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 10:00:00 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit_object(t_ray ray, t_object *obj, t_hit *tmp)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj, tmp));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, obj, tmp));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj, tmp));
	return (0);
}
