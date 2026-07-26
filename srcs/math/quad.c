/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:11:02 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/20 15:11:22 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Fill q.a, q.b, q.c, then call quad_solve().
** Returns 0 if discriminant is negative (no real roots).
** On success, q.disc and q.sqrt_disc are ready for root queries.
*/
int	quad_solve(t_quad *q)
{
	q->disc = q->b * q->b - 4.0 * q->a * q->c;
	if (q->disc < 0.0)
		return (0);
	q->sqrt_disc = sqrt(q->disc);
	return (1);
}

/* smaller root — front surface for outside rays */
double	quad_root1(t_quad *q)
{
	return ((-q->b - q->sqrt_disc) / (2.0 * q->a));
}

/* larger root — back surface, used when ray starts inside */
double	quad_root2(t_quad *q)
{
	return ((-q->b + q->sqrt_disc) / (2.0 * q->a));
}

/*
** Try root1 first, fall back to root2.
** Returns 1 and writes the nearest positive t, 0 if both are behind.
** Perfect for sphere and any future second-degree object (cone etc.)
*/
int	quad_nearest(t_quad *q, double *t)
{
	*t = quad_root1(q);
	if (*t >= EPSILON)
		return (1);
	*t = quad_root2(q);
	if (*t >= EPSILON)
		return (1);
	return (0);
}
