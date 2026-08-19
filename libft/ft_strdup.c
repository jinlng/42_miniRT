/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:05:10 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 18:30:48 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}
/*
int	main(void)
{
	char	*ft_result;
	char	*std_result;

	ft_result = ft_strdup("Hello, 42!");
	std_result = strdup("Hello, 42!");

	printf("ft_strdup: %s\n", ft_result);
	printf("strdup:    %s\n", std_result);

	free(ft_result);
	free(std_result);
	return (0);
}*/
