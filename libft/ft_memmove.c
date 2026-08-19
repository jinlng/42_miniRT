/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:03:10 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:58:18 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d == s || n == 0)
		return (dst);
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dst);
}
/*
int main(void)
{
	char a[16] = "ABCDEFGHIJ";
	char b[16] = "ABCDEFGHIJ";
	char c[16] = "ABCDEFGHIJ";

	ft_memmove(a + 2, a, 5);
	printf("right shift : %s\n", a);

	ft_memmove(b, b + 2, 5);
	printf("left shift  : %s\n", b);

	ft_memmove(c, "hello", 6);
	printf("no overlap  : %s\n", c);
	return 0;
}*/
