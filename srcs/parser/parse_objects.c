/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:51:31 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/03 18:00:35 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*new_object(t_obj_type type)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		error_exit("malloc failed");
	obj->type = type;
	obj->next = NULL;
	return (obj);
}

void	append_object(t_scene *scene, t_object *obj)
{
	t_object	*cursor;

	if (!scene->objects)
	{
		scene->objects = obj;
		return ;
	}
	cursor = scene->objects;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = obj;
}
