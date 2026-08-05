/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 16:15:06 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/15 16:57:06 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** 辅助函数：计算相机的右向量 (right)
*/
t_vec3	get_cam_right(t_vec3 dir)
{
	t_vec3	world_up;

	if (fabs(dir.y) < 0.99)
		world_up = vec3(0, 1, 0);
	else
		world_up = vec3(0, 0, 1);
	return (vec3_norm(vec3_cross(dir, world_up)));
}

/*
** 根据按键修改相机坐标
*/
void	move_camera(int key, t_camera *cam, double speed)
{
	t_vec3	right;

	right = get_cam_right(cam->dir);
	if (key == 119)
		cam->pos = vec3_add(cam->pos, vec3_scale(cam->dir, speed));
	else if (key == 115)
		cam->pos = vec3_sub(cam->pos, vec3_scale(cam->dir, speed));
	else if (key == 100)
		cam->pos = vec3_add(cam->pos, vec3_scale(right, speed));
	else if (key == 97)
		cam->pos = vec3_sub(cam->pos, vec3_scale(right, speed));
}
