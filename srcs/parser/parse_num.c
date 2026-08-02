/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 19:56:30 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/02 20:00:26 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	parse_integer(const char **str)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

double	parse_fraction(const char **str)
{
	double	result;
	double	factor;

	result = 0.0;
	factor = 0.1;
	if (**str != '.')
		return (0.0);
	(*str)++;
	while (ft_isdigit(**str))
	{
		result += (**str - '0') * factor;
		factor *= 0.1;
		(*str)++;
	}
	return (result);
}

double	ft_strtod(const char *str, const char **endptr)
{
	double	value;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = parse_sign(&str);
	value = parse_integer(&str);
	value += parse_fraction(&str);
	if (endptr)
		*endptr = str;
	return (value * sign);
}
