/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:51:15 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:51:17 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    parse_camera(char **tokens, t_scene *scene)
{
    if (scene->has_camera)
        error_exit("camera (C) defined more than once");
    if (token_count(tokens) != 4)
        error_exit("camera: expected 'C <x,y,z> <dx,dy,dz> <fov>'");
    scene->camera.pos = parse_vec3(tokens[1]);
    scene->camera.dir = parse_normal(tokens[2]);
    scene->camera.fov = parse_double(tokens[3]);
    if (scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
        error_exit("camera FOV must be in [0, 180]");
    scene->has_camera = 1;
}
