/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:13:13 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:58:06 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}
/*
int	main(void)
{
	unsigned char	ft_dst[16];
	unsigned char	libc_dst[16];
	unsigned char	src[] = "libft test";
	size_t			i;

	ft_memcpy(ft_dst, src, sizeof(src));
	memcpy(libc_dst, src, sizeof(src));
	printf("ft_memcpy : ");
	for (i = 0; i < sizeof(src); i++)
		printf("%c", ft_dst[i]);
	printf("\n");
	printf("memcpy    : ");
	for (i = 0; i < sizeof(src); i++)
		printf("%c", libc_dst[i]);
	printf("\n");
	return (0);
}*/
