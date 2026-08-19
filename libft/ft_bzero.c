/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:50:50 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:55:14 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	unsigned char	ft_buf[8];
	unsigned char	libc_buf[8];
	size_t			i;

	ft_memset(ft_buf, 'A', sizeof(ft_buf));
	ft_memset(libc_buf, 'A', sizeof(libc_buf));
	ft_bzero(ft_buf, sizeof(ft_buf));
	bzero(libc_buf, sizeof(libc_buf));
	printf("ft_bzero   : ");
	for (i = 0; i < sizeof(ft_buf); i++)
		printf("%02x ", ft_buf[i]);
	printf("\n");
	printf("bzero      : ");
	for (i = 0; i < sizeof(libc_buf); i++)
		printf("%02x ", libc_buf[i]);
	printf("\n");
	return (0);
}*/
