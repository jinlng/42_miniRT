/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:07:54 by azaytsev          #+#    #+#             */
/*   Updated: 2026/08/19 14:07:54 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	parity(t_vec3 p, double size)
{
	int	sum;

	sum = (int)floor(p.x / size) + (int)floor(p.y / size)
		+ (int)floor(p.z / size);
	if (sum % 2)
		return (1);
	return (0);
}

void	apply_checker(t_hit *hit, t_material *tmp)
{
	if (!hit->mat->checkerboard || hit->mat->checker_size <= 0)
		return ;
	*tmp = *(hit->mat);
	if (parity(hit->point, tmp->checker_size))
	{
		tmp->color.r = 1.0 - tmp->color.r;
		tmp->color.g = 1.0 - tmp->color.g;
		tmp->color.b = 1.0 - tmp->color.b;
	}
	hit->mat = tmp;
}
