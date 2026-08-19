/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 07:23:38 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:57:40 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ss;
	unsigned char		cc;
	size_t				nn;

	if (n == 0)
		return (NULL);
	ss = (const unsigned char *)s;
	cc = (unsigned char) c;
	nn = 0;
	while (nn < n)
	{
		if (ss[nn] == cc)
			return ((void *)(ss + nn));
		nn++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	buf[] = "ABC\0DEF";
	char	*ft_result;
	char	*libc_result;

	ft_result = ft_memchr(buf, 'D', sizeof(buf));
	libc_result = memchr(buf, 'D', sizeof(buf));
	printf("ft_memchr  : %s\n", ft_result);
	printf("memchr     : %s\n", libc_result);
	ft_result = ft_memchr(buf, 'Z', sizeof(buf));
	libc_result = memchr(buf, 'Z', sizeof(buf));
	printf("ft_memchr Z: %p\n", (void *)ft_result);
	printf("memchr Z   : %p\n", (void *)libc_result);
	return (0);
}*/
