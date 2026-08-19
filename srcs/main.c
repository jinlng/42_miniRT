/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:10:53 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/21 11:21:48 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		error_exit("usage: ./miniRT <scene.rt>");
	parse_scene(argv[1], &app.scene);
	mlx_setup(&app);
	render(&app);
	mlx_mouse_hook(app.mlx.win, mouse_hook, &app);
	mlx_hook(app.mlx.win, 2, 1L << 0, (int (*)())(void *)key_handler, &app);
	mlx_hook(app.mlx.win, 17, 0, (int (*)())(void *)close_handler, &app);
	mlx_loop(app.mlx.ptr);
	return (0);
}

void	error_exit(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}
