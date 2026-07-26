/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:02:01 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 15:22:44 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Full shading: ambient + diffuse over every light.
** Specular term is stubbed as a comment — drop it in for bonus.*/
t_color	shade(t_hit *hit, t_scene *scene, t_ray ray)
{
	t_color	final;
	t_light	*light;

	final = ambient_light(hit, &scene->ambient);
	light = scene->lights;
	while (light)
	{
		if (!in_shadow(scene, hit, light))
		{
			final = color_add(final, diffuse_light(hit, light));
			final = color_add(final, specular_light(hit, light, ray));
		}
		light = light->next;
	}
	return (color_clamp(final));
}
