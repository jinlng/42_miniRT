/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 16:33:08 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 23:48:05 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	count_tokens(const char *line)
{
	char	*buf;
	char	*tok;
	int		count;

	buf = strdup(line);
	if (!buf)
		error_exit("malloc failed");
	count = 0;
	tok = strtok(buf, " \t\r\n");
	while (tok)
	{
		count++;
		tok = strtok(NULL, " \t\r\n");
	}
	free(buf);
	return (count);
}

char	**split_line(const char *line)
{
	char	**tokens;
	char	*buf;
	char	*tok;
	int		i;

	tokens = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens)
		error_exit("malloc failed");
	buf = strdup(line);
	tok = strtok(buf, " \t\r\n");
	i = 0;
	while (tok)
	{
		tokens[i++] = strdup(tok);
		tok = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	free(buf);
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
