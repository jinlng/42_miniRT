/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:48:03 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/03 17:49:35 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;

	if (token_count(tokens) < 4)
		error_exit("sphere: expected 'sp <x,y,z> <diameter> <r,g,b>'");
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

	if (token_count(tokens) < 4)
		error_exit("plane: expected 'pl <x,y,z> <nx,ny,nz> <r,g,b>'");
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

	if (token_count(tokens) < 6)
		error_exit("cylinder: expected 'cy <x,y,z> <ax,ay,az> <diameter> <height> <r,g,b>'");
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
void    parse_cone(char **tokens, t_scene *scene)
{
    t_object    *obj;

    if (token_count(tokens) < 6)
        error_exit("cone: 'co <apex> <axis> <radius> <height> <color>'");
    obj = new_object(OBJ_CONE);
    obj->cone.apex   = parse_vec3(tokens[1]);
    obj->cone.axis   = parse_normal(tokens[2]);
    obj->cone.radius = parse_double(tokens[3]);
    if (obj->cone.radius <= 0)
        error_exit("cone radius must be positive");
    obj->cone.height = parse_double(tokens[4]);
    if (obj->cone.height <= 0)
        error_exit("cone height must be positive");
    obj->mat = default_material(parse_color(tokens[5]));
    parse_material(tokens, 5, &obj->mat);
    append_object(scene, obj);
}

/*
** tr <v0 x,y,z> <v1 x,y,z> <v2 x,y,z> <r,g,b> [material]
** Normal is precomputed: cross(v1-v0, v2-v0)
** Order of vertices determines which face is front (right-hand rule).
*/
void    parse_triangle(char **tokens, t_scene *scene)
{
    t_object    *obj;
    t_vec3      e1;
    t_vec3      e2;

    if (token_count(tokens) < 5)
        error_exit("triangle: 'tr <v0> <v1> <v2> <color>'");
    obj = new_object(OBJ_TRIANGLE);
    obj->triangle.v0 = parse_vec3(tokens[1]);
    obj->triangle.v1 = parse_vec3(tokens[2]);
    obj->triangle.v2 = parse_vec3(tokens[3]);
    e1 = vec3_sub(obj->triangle.v1, obj->triangle.v0);
    e2 = vec3_sub(obj->triangle.v2, obj->triangle.v0);
    obj->triangle.normal = vec3_norm(vec3_cross(e1, e2));
    if (vec3_near_zero(obj->triangle.normal))
        error_exit("triangle: degenerate (vertices are collinear)");
    obj->mat = default_material(parse_color(tokens[4]));
    parse_material(tokens, 4, &obj->mat);
    append_object(scene, obj);
}