/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:50:28 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:50:28 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void error_exit(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

double parse_double(const char *s)
{
	char *end;
	double v;

	v = strtod(s, &end);
	if (*end != '\0')
		error_exit("invalid number");
	return (v);
}

t_color parse_color(const char *s)
{
	t_color c;
	char *buf;
	char *tok;

	buf = strdup(s);
	tok = strtok(buf, ",");
	if (!tok)
		error_exit("invalid color");
	c.r = (int)parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid color");
	c.g = (int)parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid color");
	c.b = (int)parse_double(tok);
	free(buf);
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		error_exit("color value out of range [0,255]");
	return (c);
}

t_vec3 parse_vec3(const char *s)
{
	t_vec3 v;
	char *buf;
	char *tok;

	buf = strdup(s);
	tok = strtok(buf, ",");
	if (!tok)
		error_exit("invalid vector");
	v.x = parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid vector");
	v.y = parse_double(tok);
	tok = strtok(NULL, ",");
	if (!tok)
		error_exit("invalid vector");
	v.z = parse_double(tok);
	free(buf);
	return (v);
}

/* normalized orientation vector — must be in [-1,1] per component */
t_vec3 parse_normal(const char *s)
{
	t_vec3 v;

	v = parse_vec3(s);
	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0 || v.z < -1.0 || v.z > 1.0)
		error_exit("orientation vector components must be in [-1,1]");
	if (vec3_near_zero(v))
		error_exit("orientation vector cannot be zero");
	return (vec3_norm(v));
}

/* split on whitespace, return NULL-terminated array */
char **split_line(const char *line)
{
	char **tokens;
	char *buf;
	char *tok;
	int count;
	int i;

	buf = strdup(line);
	/* count tokens */
	count = 0;
	tok = strtok(buf, " \t\r\n");
	while (tok)
	{
		count++;
		tok = strtok(NULL, " \t\r\n");
	}
	free(buf);
	tokens = malloc(sizeof(char *) * (count + 1));
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

void free_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int token_count(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}
