/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:56:58 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 14:00:17 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	i = 0;
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/*
int	main(void)
{
	char		ft_buf[20];
	char		libc_buf[20];
	const char	*src = "Hello World";
	size_t		ft_ret;
	size_t		libc_ret;

	ft_ret = ft_strlcpy(ft_buf, src, sizeof(ft_buf));
	libc_ret = strlcpy(libc_buf, src, sizeof(libc_buf));
	printf("ft_strlcpy : %zu -> %s\n", ft_ret, ft_buf);
	printf("strlcpy    : %zu -> %s\n", libc_ret, libc_buf);
	return (0);
}*/
