/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:48:03 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 23:48:04 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;

	check_count(tokens, 4, "sphere: expected 'sp <x,y,z> <diameter> <r,g,b>'");
	obj = new_object(OBJ_SPHERE);
	obj->sphere.center = parse_vec3(tokens[1]);
	obj->sphere.radius = parse_double(tokens[2]) / 2.0;
	if (obj->sphere.radius <= 0)
		error_exit("sphere diameter must be positive");
	obj->mat = default_material(parse_color(tokens[3]));
	parse_material(tokens, 3, &obj->mat);
	append_object(scene, obj);
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;

	check_count(tokens, 4, "plane: expected 'pl <x,y,z> <nx,ny,nz> <r,g,b>'");
	obj = new_object(OBJ_PLANE);
	obj->plane.point = parse_vec3(tokens[1]);
	obj->plane.normal = parse_normal(tokens[2]);
	obj->mat = default_material(parse_color(tokens[3]));
	parse_material(tokens, 3, &obj->mat);
	append_object(scene, obj);
}

void	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	*obj;

	check_count(tokens, 6, "cylinder: expected "
		"'cy <x,y,z> <ax,ay,az> <diameter> <height> <r,g,b>'");
	obj = new_object(OBJ_CYLINDER);
	obj->cylinder.center = parse_vec3(tokens[1]);
	obj->cylinder.axis = parse_normal(tokens[2]);
	obj->cylinder.radius = parse_double(tokens[3]) / 2.0;
	if (obj->cylinder.radius <= 0)
		error_exit("cylinder diameter must be positive");
	obj->cylinder.height = parse_double(tokens[4]);
	if (obj->cylinder.height <= 0)
		error_exit("cylinder height must be positive");
	obj->cylinder.top_center = vec3_add(obj->cylinder.center,
			vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2.0));
	obj->cylinder.bottom_center = vec3_sub(obj->cylinder.center,
			vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2.0));
	obj->mat = default_material(parse_color(tokens[5]));
	parse_material(tokens, 5, &obj->mat);
	append_object(scene, obj);
}

/*
** co <apex x,y,z> <ax,ay,az> <radius> <height> <r,g,b> [material]
*/
