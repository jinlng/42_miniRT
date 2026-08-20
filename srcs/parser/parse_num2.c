/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 12:42:32 by azaytsev          #+#    #+#             */
/*   Updated: 2026/08/19 12:51:33 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	scan_digits(const char *s, int *i)
{
	int	n;

	n = 0;
	while (ft_isdigit(s[*i]))
	{
		*i += 1;
		n++;
	}
	return (n);
}

int	valid_num(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (scan_digits(s, &i) == 0)
		return (0);
	if (s[i] == '.')
	{
		i++;
		if (scan_digits(s, &i) == 0)
			return (0);
	}
	return (s[i] == '\0');
}

double	next_component(const char **s, int last)
{
	char		buf[64];
	const char	*end;
	double		v;
	int			i;

	i = 0;
	while ((*s)[i] && (*s)[i] != ',' && i < 63)
	{
		buf[i] = (*s)[i];
		i++;
	}
	buf[i] = '\0';
	if (!valid_num(buf))
		error_exit("invalid number in vector or color");
	v = ft_strtod(buf, &end);
	if (v > 1000000.0 || v < -1000000.0)
		error_exit("number out of range");
	*s += i;
	if (!last && **s == ',')
		*s += 1;
	else if (!last || **s != '\0')
		error_exit("expected exactly three comma separated values");
	return (v);
}
