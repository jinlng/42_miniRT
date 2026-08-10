/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:00:00 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 23:48:04 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_count(char **tokens, int n, char *msg)
{
	if (token_count(tokens) != n)
		error_exit(msg);
}

void	parse_material(char **tokens, int color_idx, t_material *mat)
{
	(void)tokens;
	(void)color_idx;
	(void)mat;
}
