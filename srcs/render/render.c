/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:15:20 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 15:20:26 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Background: simple sky gradient when no object is hit.
** Lerp white→blue based on ray vertical direction.
*/
static t_color	background(t_ray ray)
{
	double	t;
	t_color	white;
	t_color	blue;

	// white = (t_color){255, 255, 255};
	// blue  = (t_color){128, 178, 255};
	white = (t_color){1.0, 1.0, 1.0};
	blue = (t_color){0.5, 0.7, 1.0};
	t = (ray.dir.y + 1.0) * 0.5;
	return (color_lerp(white, blue, t));
}

// t_color ray_color(t_ray ray, t_scene *scene)
// {
//     t_hit   hit;

//     if (intersect_scene(ray, scene, &hit))
//         return (shade(&hit, scene, ray));
//     return (background(ray));
// }
t_color	ray_color(t_ray ray, t_scene *scene, int depth)
{
	t_hit	hit;

	if (depth <= 0)
		return ((t_color){0.0, 0.0, 0.0});
	if (!intersect_scene(ray, scene, &hit))
		return (background(ray));
	return (shade(&hit, scene, ray));
}

static t_color	get_sample_color(t_app *app, t_camera_basis *basis, double px,
		double py)
{
	double	u;
	double	v;
	t_ray	ray;

	u = px / (double)WIDTH;
	v = 1.0 - py / (double)HEIGHT;
	ray = get_ray(basis, u, v);
	return (ray_color(ray, &app->scene, MAX_DEPTH));
}

static void	render_pixel(t_app *app, t_camera_basis *basis, int x, int y)
{
	t_color	total;
	int		i;
	int		j;

	total = (t_color){0, 0, 0};
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			/* ** 当 i, j 为 0 或 1 时：
			** (i + 0.5) / 2.0 分别等于 0.25 和 0.75 */
			total = color_add(total, get_sample_color(app, basis, x + (i + 0.5)
						/ 2.0, y + (j + 0.5) / 2.0));
		}
	}
	mlx_put_pixel(&app->mlx, x, y, color_scale(total, 0.25));
}

// static void	render_pixel(t_app *app, t_camera_basis *basis, int x, int y)
// {
// 	double	u;
// 	double	v;
// 	t_ray	ray;
// 	t_color	color;

// 	u = (x + 0.5) / (double)WIDTH;
// 	v = 1.0 - (y + 0.5) / (double)HEIGHT;
// 	ray = get_ray(basis, u, v);
// 	color = ray_color(ray, &app->scene);
// 	mlx_put_pixel(&app->mlx, x, y, color);
// }

void	render(t_app *app)
{
	t_camera_basis	basis;
	int				x;
	int				y;

	basis = build_camera_basis(&app->scene.camera);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			render_pixel(app, &basis, x, y);
	}
	mlx_put_image_to_window(app->mlx.ptr, app->mlx.win, app->mlx.img, 0, 0);
}

// void    render(t_app *app)
// {
//     t_camera_basis  basis;
//     t_ray           ray;
//     t_color         color;
//     double          u;
//     double          v;
//     int             x;
//     int             y;

//     basis = build_camera_basis(&app->scene.camera);
//     y = 0;
//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             u = (x + 0.5) / (double)WIDTH;
//             v = 1.0 - (y + 0.5) / (double)HEIGHT;
//             ray = get_ray(&basis, u, v);
//             color = ray_color(ray, &app->scene);
//             mlx_put_pixel(&app->mlx, x, y, color);
//             x++;
//         }
//         y++;
//     }
//     mlx_put_image_to_window(app->mlx.ptr, app->mlx.win, app->mlx.img, 0, 0);
// }
