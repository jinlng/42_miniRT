/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:11:11 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/15 14:11:57 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec3_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_norm(t_vec3 v)
{
	double	len;

	len = vec3_len(v);
	if (len < 1e-12)
		return (vec3(0, 0, 0));
	return (vec3_scale(v, 1.0 / len));
}

int	vec3_near_zero(t_vec3 v)
{
	return (fabs(v.x) < 1e-8 && fabs(v.y) < 1e-8 && fabs(v.z) < 1e-8);
}
