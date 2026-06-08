/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:51:41 by jinliang          #+#    #+#             */
/*   Updated: 2026/06/03 16:51:43 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* read one line from fd into a heap buffer — basic gnl replacement */
static char *read_line(int fd)
{
    char    *line;
    char    c;
    int     i;
    int     ret;

    line = malloc(4096);
    if (!line) error_exit("malloc failed");
    i = 0;
    while (i < 4095)
    {
        ret = read(fd, &c, 1);
        if (ret == 0 || c == '\n')
            break ;
        if (ret < 0)
            error_exit("read error");
        line[i++] = c;
    }
    line[i] = '\0';
    if (i == 0 && ret == 0)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

static void dispatch(char **tokens, t_scene *scene)
{
    if (!tokens || !tokens[0])
        return ;
    if (tokens[0][0] == '#')    /* comment line */
        return ;
    if (!strcmp(tokens[0], "A"))
        parse_ambient(tokens, scene);
    else if (!strcmp(tokens[0], "C"))
        parse_camera(tokens, scene);
    else if (!strcmp(tokens[0], "L"))
        parse_light(tokens, scene);
    else if (!strcmp(tokens[0], "sp"))
        parse_sphere(tokens, scene);
    else if (!strcmp(tokens[0], "pl"))
        parse_plane(tokens, scene);
    else if (!strcmp(tokens[0], "cy"))
        parse_cylinder(tokens, scene);
    else
    {
        write(2, "Error\nunknown identifier: ", 26);
        write(2, tokens[0], strlen(tokens[0]));
        write(2, "\n", 1);
        exit(1);
    }
}

void    parse_scene(const char *file, t_scene *scene)
{
    int     fd;
    char    *line;
    char    **tokens;

    /* validate extension */
    if (strlen(file) < 3
        || strcmp(file + strlen(file) - 3, ".rt") != 0)
        error_exit("scene file must have .rt extension");
    fd = open(file, O_RDONLY);
    if (fd < 0)
        error_exit("cannot open scene file");
    memset(scene, 0, sizeof(t_scene));
    while (1)
    {
        line = read_line(fd);
        if (!line)
            break ;
        if (line[0] == '\0') { free(line); continue ; } /* blank line */
        tokens = split_line(line);
        free(line);
        dispatch(tokens, scene);
        free_tokens(tokens);
    }
    close(fd);
    /* mandatory element checks */
    if (!scene->has_ambient)
        error_exit("scene missing ambient lighting (A)");
    if (!scene->has_camera)
        error_exit("scene missing camera (C)");
    if (!scene->has_light)
        error_exit("scene missing light (L)");
}
