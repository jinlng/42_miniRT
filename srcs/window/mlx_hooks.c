/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:15:43 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 17:37:34 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)x;
	(void)y;
	if (app->is_locked)
		return (0);
	if (button == 4)
	{
		app->scene.camera.fov -= 5;
		if (app->scene.camera.fov < 1)
			app->scene.camera.fov = 1;
	}
	else if (button == 5)
	{
		app->scene.camera.fov += 5;
		if (app->scene.camera.fov > 179)
			app->scene.camera.fov = 179;
	}
	else
		return (0);
	render(app);
	return (0);
}

int	key_handler(int keycode, void *param)
{
	t_app	*app;
	double	move_speed;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		close_handler(app);
	if (keycode == KEY_SPACE)
	{
		app->is_locked = !app->is_locked;
		if (app->is_locked)
			ft_putstr_fd("🔒 Camera Locked\n", 1);
		else
			ft_putstr_fd("🔓 Camera Unlocked\n", 1);
		return (0);
	}
	if (app->is_locked)
		return (0);
	move_speed = 0.5;
	if (keycode == 119 || keycode == 115 || keycode == 100 || keycode == 97)
	{
		move_camera(keycode, &app->scene.camera, move_speed);
		render(app);
	}
	return (0);
}

int	close_handler(t_app *app)
{
	mlx_destroy_image(app->mlx.ptr, app->mlx.img);
	mlx_destroy_window(app->mlx.ptr, app->mlx.win);
	free_scene(&app->scene);
	exit(0);
}
