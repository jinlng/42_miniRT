/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:05:05 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 16:00:21 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ambient_light(t_hit *hit, t_ambient *ambient)
{
	t_color	color;

	color = color_multiply(hit->mat->color, ambient->color);
	return (color_scale(color, ambient->ratio));
}
