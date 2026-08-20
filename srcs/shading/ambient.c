/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:05:05 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/10 17:30:54 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ambient_light(t_hit *hit, t_ambient *ambient)
{
	t_color	amb_light;

	amb_light = color_scale(ambient->color, ambient->ratio);
	return (color_multiply(hit->mat->color, amb_light));
}
