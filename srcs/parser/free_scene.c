/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:13:11 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/15 14:13:12 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*next_obj;
	t_light		*light;
	t_light		*next_light;

	obj = scene->objects;
	while (obj)
	{
		next_obj = obj->next;
		free(obj);
		obj = next_obj;
	}
	light = scene->lights;
	while (light)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
}
