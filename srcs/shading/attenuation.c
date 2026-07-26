/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attenuation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:49:50 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 16:26:21 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	attenuation(t_light *light, t_vec3 hit_point)
{
	double	d;
	double	att;

	d = vec3_len(vec3_sub(light->pos, hit_point));
	att = 1.0 / (light->kc + light->kl * d + light->kq * d * d);
	if (att > 1.0)
		att = 1.0;
	return (att);
}
