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
	char	*end;
	double	v;

	v = strtod(s, &end);
	if (*end != '\0')
		error_exit("invalid number");
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
	char	*buf;
	char	*tok;

	buf = strdup(s);
	if (!buf)
		error_exit("malloc failed");
	tok = strtok(buf, ",");
	if (!tok)
		error_exit("invalid color");
	c.r = (int)parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid color");
	c.g = (int)parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid color");
	c.b = (int)parse_double(tok);
	free(buf);
	if (c.r < 0.0 || c.r > 255.0 || c.g < 0.0 || c.g > 255.0 || c.b < 0.0
		|| c.b > 255.0)
		error_exit("color value out of range [0,255]");
	return ((t_color){c.r / 255.0, c.g / 255.0, c.b / 255.0});
}

t_vec3	parse_vec3(const char *s)
{
	t_vec3	v;
	char	*buf;
	char	*tok;

	buf = strdup(s);
	tok = strtok(buf, ",");
	if (!tok)
		error_exit("invalid vector");
	v.x = parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid vector");
	v.y = parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid vector");
	v.z = parse_double(tok);
	free(buf);
	return (v);
}

/* normalized orientation vector — must be in [-1,1] per component */
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
