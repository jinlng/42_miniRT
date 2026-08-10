/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:01:10 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 23:48:02 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
