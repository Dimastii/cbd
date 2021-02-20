/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:33:30 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 00:00:52 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			reed_map(char *line, t_vars *vars, int *i)
{
	static int flag;
	static int local_map_h;

	if (flag != 1 && *line == '\0')
	{
		(*i)++;
		return (0);
	}
	else
	{
		flag = 1;
		vars->map_h++;
		if (vars->map_w < ft_strlen(line))
			vars->map_w = ft_strlen(line);
	}
	return (0);
}

void		skip_line(char **line, t_vars *vars, int *i, int fd)
{
	reed_map(*line, vars, i);
	(*i)++;
	free(*line);
	while (get_next_line(fd, line))
	{
		reed_map(*line, vars, i);
		free(*line);
	}
	free(*line);
	get_next_line(fd, line);
	reed_map(*line, vars, i);
	free(*line);
	close(fd);
}

void		get_map(char **line, t_vars *vars, int *i, int fd)
{
	while (--(*i) != 0)
	{
		get_next_line(fd, line);
		free(*line);
	}
	vars->map = malloc(sizeof(char **) * (vars->map_h + 1));
	vars->map[vars->map_h + 1] = NULL;
	while (*i < vars->map_h)
	{
		get_next_line(fd, line);
		if (**line == '\0')
			print_error("ERROR : find \\n after map");
		vars->map[*i] = ft_strdup_cd(*line, vars->map_w);
		(*i)++;
		free(*line);
	}
}
