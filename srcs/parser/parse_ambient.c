/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:51:08 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:51:08 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    parse_ambient(char **tokens, t_scene *scene)
{
    if (scene->has_ambient)
        error_exit("ambient lighting (A) defined more than once");
    if (token_count(tokens) != 3)
        error_exit("ambient: expected 'A <ratio> <r,g,b>'");
    scene->ambient.ratio = parse_double(tokens[1]);
    if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
        error_exit("ambient ratio must be in [0.0, 1.0]");
    scene->ambient.color = parse_color(tokens[2]);
    scene->has_ambient = 1;
}