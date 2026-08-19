/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 00:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 14:00:09 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	while (dlen < size && dst[dlen])
		dlen++;
	slen = ft_strlen(src);
	if (dlen == size)
		return (slen + size);
	i = 0;
	while (src[i] && (dlen + 1 + i) < size)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
/*
int	main(void)
{
	char		ft_buf[20] = "Hello ";
	char		libc_buf[20] = "Hello ";
	const char	*src = "World";
	size_t		ft_ret;
	size_t		libc_ret;

	ft_ret = ft_strlcat(ft_buf, src, sizeof(ft_buf));
	libc_ret = strlcat(libc_buf, src, sizeof(libc_buf));
	printf("ft_strlcat : %zu -> %s\n", ft_ret, ft_buf);
	printf("strlcat    : %zu -> %s\n", libc_ret, libc_buf);
	return (0);
}*/
