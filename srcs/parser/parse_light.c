/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:51:23 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:51:25 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    parse_light(char **tokens, t_scene *scene)
{
    t_light *light;
    t_light *cursor;

    if (token_count(tokens) != 4)
        error_exit("light: expected 'L <x,y,z> <brightness> <r,g,b>'");
    light = malloc(sizeof(t_light));
    if (!light) error_exit("malloc failed");
    light->pos = parse_vec3(tokens[1]);
    light->brightness = parse_double(tokens[2]);
    if (light->brightness < 0.0 || light->brightness > 1.0)
        error_exit("light brightness must be in [0.0, 1.0]");
    light->color = parse_color(tokens[3]);
    light->next = NULL;
    /* append to list */
    if (!scene->lights)
        scene->lights = light;
    else
    {
        cursor = scene->lights;
        while (cursor->next)
            cursor = cursor->next;
        cursor->next = light;
    }
    scene->has_light = 1;
}
