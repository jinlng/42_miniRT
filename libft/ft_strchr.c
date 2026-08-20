/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 05:51:17 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:59:37 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*
int	main(void)
{
	const char	*str = "Hello World";
	char		*ft_result;
	char		*libc_result;

	ft_result = ft_strchr(str, 'W');
	libc_result = strchr(str, 'W');
	printf("ft_strchr  : %s\n", ft_result);
	printf("strchr     : %s\n", libc_result);
	ft_result = ft_strchr(str, 'Z');
	libc_result = strchr(str, 'Z');
	printf("ft_strchr Z: %p\n", (void *)ft_result);
	printf("strchr Z   : %p\n", (void *)libc_result);
	return (0);
}*/
