/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 06:12:11 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 18:30:48 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len
			&& big[i + j]
			&& little[j]
			&& big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	*big = "Hello World";
	const char	*little = "World";
	char		*result;

	result = ft_strnstr(big, little, 20);
	printf("ft_strnstr (len=20): %s\n", result);
	result = ft_strnstr(big, little, 5);
	printf("ft_strnstr (len=5) : %p\n", (void *)result);
	result = ft_strnstr(big, "Hello", 20);
	printf("ft_strnstr \"Hello\" : %s\n", result);
	return (0);
}*/
