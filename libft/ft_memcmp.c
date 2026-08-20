/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:46:45 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:57:52 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;
	size_t				nn;

	us1 = (const unsigned char *)s1;
	us2 = (const unsigned char *)s2;
	nn = 0;
	while (nn < n)
	{
		if (us1[nn] != us2[nn])
			return ((int)us1[nn] - (int)us2[nn]);
		nn++;
	}
	return (0);
}
/*
int main(void)
{
	const char a[] = {0x41, 0x42, 0xC8, 0x00};
	const char b[] = {0x41, 0x42, 0x7F, 0x00};

	printf("n=2  -> %d (std %d)\n",
		ft_memcmp(a, b, 2), memcmp(a, b, 2)); 
	printf("n=3  -> %d (std %d)\n",
		ft_memcmp(a, b, 3), memcmp(a, b, 3)); 
	printf("n=0  -> %d (std %d)\n",
		ft_memcmp(a, b, 0), memcmp(a, b, 0)); 

	printf("'abc' vs 'abd' (n=3): %d\n",
		ft_memcmp("abc", "abd", 3));
	return 0;
}*/
