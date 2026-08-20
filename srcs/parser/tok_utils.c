/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 16:33:08 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/19 12:51:33 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	count_tokens(const char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i])
			count++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	return (count);
}

static char	*word_dup(const char *s, int len)
{
	char	*w;
	int		i;

	w = malloc((size_t)len + 1);
	if (!w)
		error_exit("malloc failed");
	i = 0;
	while (i < len)
	{
		w[i] = s[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

char	**split_line(const char *line)
{
	char	**tokens;
	int		i;
	int		start;
	int		t;

	tokens = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens)
		error_exit("malloc failed");
	i = 0;
	t = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		start = i;
		while (line[i] && !ft_isspace(line[i]))
			i++;
		if (i > start)
			tokens[t++] = word_dup(line + start, i - start);
	}
	tokens[t] = NULL;
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int	token_count(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}
