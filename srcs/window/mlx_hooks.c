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
	if (app->is_locked) /* 如果锁定状态，忽略鼠标滚轮 */
		return (0);
	if (button == 4) // 滚轮向上 -> 视野变窄 -> 放大
	{
		app->scene.camera.fov -= 5;
		if (app->scene.camera.fov < 1) // 限制最小 FOV 避免画面反转
			app->scene.camera.fov = 1;
	}
	else if (button == 5) // 滚轮向下 -> 视野变宽 -> 缩小
	{
		app->scene.camera.fov += 5;
		if (app->scene.camera.fov > 179) // 限制最大 FOV 避免拉伸畸变
			app->scene.camera.fov = 179;
	}
	else
		return (0);
	// 重新计算相机基底并渲染
	render(app);
	return (0);
}

int	key_handler(int keycode, void *param)
{
	t_app	*app;
	double	move_speed;

	app = (t_app *)param;
	if (keycode == KEY_ESC) /* ESC 键退出 */
		close_handler(app);
	if (keycode == KEY_SPACE) /* 空格键切换锁定状态 */
	{
		app->is_locked = !app->is_locked;
		if (app->is_locked)
			ft_putstr_fd("🔒 Camera Locked\n", 1);
		else
			ft_putstr_fd("🔓 Camera Unlocked\n", 1);
		return (0);
	}
	if (app->is_locked) /* 如果锁定状态，忽略移动按键 */
		return (0);
	move_speed = 0.5; /* 每次移动的距离，可根据需要调整 */
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