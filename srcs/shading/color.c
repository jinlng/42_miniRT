/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:52:29 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/14 17:22:18 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color color_scale(t_color c, double t)
{
    return ((t_color){c.r * t, c.g * t, c.b * t});
}

t_color color_add(t_color a, t_color b)
{
    return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

/*Component-wise multiply, normalized by 255 
  Used to tint object color by light color or ambient color*/
t_color color_multiply(t_color a, t_color b)
{
    return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}
/* Clamp color components to [0.0, 1.0] range.
Always call this as the last step before writing a pixel.*/
t_color	color_clamp(t_color c)
{
	t_color	out;

	out.r = c.r;
	out.g = c.g;
	out.b = c.b;
	if (out.r < 0.0)
		out.r = 0;
	if (out.r > 1.0)
		out.r = 1.0;
	if (out.g < 0.0)
		out.g = 0;
	if (out.g > 1.0)
		out.g = 1.0;
	if (out.b < 0.0)
		out.b = 0;
	if (out.b > 1.0)
		out.b = 1.0;
	return (out);
}

/*
** Linear interpolation between two colors.
** t = 0.0 → a,  t = 1.0 → b.
** Used for: checkerboard, sky gradient, glossy mixing.
*/
t_color color_lerp(t_color a, t_color b, double t)
{
    return (color_clamp(color_add(
        color_scale(a, 1.0 - t),
        color_scale(b, t)
    )));
}