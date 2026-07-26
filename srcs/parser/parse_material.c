/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:17:04 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/21 11:21:48 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_material(char **tokens, int color_idx, t_material *mat)
{
	int	count;

	count = token_count(tokens);
	if (count > color_idx + 1)
		mat->ks = parse_ratio(tokens[color_idx + 1]);
	if (count > color_idx + 2)
		mat->shininess = parse_double(tokens[color_idx + 2]);
	if (mat->shininess < 1.0)
		error_exit("Material shininess must be >= 1.0");
	if (count > color_idx + 3)
		mat->reflectivity = parse_ratio(tokens[color_idx + 3]);
	if (count > color_idx + 4)
		mat->transparency = parse_ratio(tokens[color_idx + 4]);
	if (count > color_idx + 5)
		mat->ior = parse_double(tokens[color_idx + 5]);
	if (mat->ior < 1.0)
		error_exit("Material index of refraction must be >= 1.0");
	if (count > color_idx + 6)
		mat->checkerboard = (int)parse_double(tokens[color_idx + 6]);
	if (count > color_idx + 7)
		mat->checker_size = parse_double(tokens[color_idx + 7]);
}

t_material	default_material(t_color color)
{
	t_material	m;

	m.color = color;
	m.ka = 0.1;
	m.kd = 0.9;
	m.ks = 0.3;
	m.shininess = 32.0;
	m.reflectivity = 0.0;
	m.transparency = 0.0;
	m.ior = 1.0;
	m.roughness = 0.0;
	m.checkerboard = 0;
	m.checker_size = 1.0;
	return (m);
}
