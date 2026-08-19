/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:48:41 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 14:00:33 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
/*
int	main(void)
{
	const char	*test = "Hello, world!";

	printf("ft_strlen : %zu\n", ft_strlen(test));
	printf("strlen    : %zu\n", strlen(test));
	return (0);
}*/
