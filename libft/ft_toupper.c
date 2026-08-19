/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 07:18:17 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 14:02:26 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int	main(void)
{
	printf("ft_toupper('a') : %c\n", ft_toupper('a'));
	printf("toupper('a')    : %c\n", toupper('a'));
	printf("ft_toupper('Z') : %c\n", ft_toupper('Z'));
	printf("toupper('Z')    : %c\n", toupper('Z'));
	printf("ft_toupper('5') : %c\n", ft_toupper('5'));
	printf("toupper('5')    : %c\n", toupper('5'));
	return (0);
}*/
