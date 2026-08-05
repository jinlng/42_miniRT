/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 16:20:39 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/15 15:35:59 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Write one pixel into the image buffer.
** Never call mlx_pixel_put — it's extremely slow (one syscall per pixel).
** We write into the raw buffer and flush once per frame instead.*/
void	mlx_put_pixel(t_mlx *mlx, int x, int y, t_color color)
{
	char	*dst;
	int		argb;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	argb = (0 << 24) | ((int)(color.r * 255.999) << 16)
		| ((int)(color.g * 255.999) << 8) | (int)(color.b * 255.999);
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = argb;
}
