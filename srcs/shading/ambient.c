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

	// 1. 计算环境光的实际强度颜色 (Ambient_Color * Ratio)
	amb_light = color_scale(hit->mat->color, ambient->ratio * hit->mat->ka);
	// 2. 将环境光叠加到物体固有色上 (Material_Color * Ambient_Light)
	return (color_multiply(hit->mat->color, amb_light));
}
