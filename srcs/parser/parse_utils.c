/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:50:28 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 16:32:21 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	parse_double(const char *s)
{
	const char	*end;
	double		v;

	if (!valid_num(s))
		error_exit("invalid number");
	v = ft_strtod(s, &end);
	if (*end != '\0')
		error_exit("invalid number");
	if (v > 1000000.0 || v < -1000000.0)
		error_exit("number out of range");
	return (v);
}

double	parse_ratio(const char *s)
{
	double	value;

	value = parse_double(s);
	if (value < 0.0 || value > 1.0)
		error_exit("Material ratio out of range");
	return (value);
}

t_color	parse_color(const char *s)
{
	t_color	c;
	double	v[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		v[i] = next_component(&s, i == 2);
		if (v[i] < 0.0 || v[i] > 255.0 || v[i] != (int)v[i])
			error_exit("color values must be integers in [0,255]");
		i++;
	}
	c.r = v[0] / 255.0;
	c.g = v[1] / 255.0;
	c.b = v[2] / 255.0;
	return (c);
}

t_vec3	parse_vec3(const char *s)
{
	t_vec3	v;

	v.x = next_component(&s, 0);
	v.y = next_component(&s, 0);
	v.z = next_component(&s, 1);
	return (v);
}

t_vec3	parse_normal(const char *s)
{
	t_vec3	v;

	v = parse_vec3(s);
	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0 || v.z < -1.0
		|| v.z > 1.0)
		error_exit("orientation vector components must be in [-1,1]");
	if (vec3_near_zero(v))
		error_exit("orientation vector cannot be zero");
	return (vec3_norm(v));
}
