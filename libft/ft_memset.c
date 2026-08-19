/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:54:42 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:58:28 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	unsigned char	ft_buf[8];
	unsigned char	libc_buf[8];
	size_t			i;

	ft_memset(ft_buf, 'A', sizeof(ft_buf));
	memset(libc_buf, 'A', sizeof(libc_buf));
	printf("ft_memset  : ");
	for (i = 0; i < sizeof(ft_buf); i++)
		printf("%c", ft_buf[i]);
	printf("\n");
	printf("memset     : ");
	for (i = 0; i < sizeof(libc_buf); i++)
		printf("%c", libc_buf[i]);
	printf("\n");
	return (0);
}*/
