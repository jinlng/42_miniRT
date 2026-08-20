/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 06:07:53 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 14:01:09 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	size_t			i;
	const char		*last;

	uc = (unsigned char)c;
	i = 0;
	last = NULL;
	while (s[i])
	{
		if ((unsigned char)s[i] == uc)
			last = s + i;
		i++;
	}
	if (uc == '\0')
		return ((char *)(s + i));
	return ((char *)last);
}
/*
int	main(void)
{
	const char	*str = "Hello World";
	char		*ft_result;
	char		*libc_result;

	ft_result = ft_strrchr(str, 'o');
	libc_result = strrchr(str, 'o');
	printf("ft_strrchr  : %s\n", ft_result);
	printf("strrchr     : %s\n", libc_result);
	ft_result = ft_strrchr(str, 'Z');
	libc_result = strrchr(str, 'Z');
	printf("ft_strrchr Z: %p\n", (void *)ft_result);
	printf("strrchr Z   : %p\n", (void *)libc_result);
	return (0);
}*/
