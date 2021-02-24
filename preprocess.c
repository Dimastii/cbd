/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:37:20 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 17:54:14 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		print_error(char *mode)
{
	write(2, mode, ft_strlen(mode));
	ft_exit();
}

int			resolution(char *line, t_vars *vars)
{
	static int count_call;

	if (*line == 'R')
	{
		line++;
		vars->size_win_w = ft_atoi_cb(&line);
		vars->size_win_h = ft_atoi_cb(&line);
		if (vars->size_win_w > 2560 && vars->mode_gl == 1)
			vars->size_win_w = 2560;
		if (vars->size_win_h > 1440 && vars->mode_gl == 1)
			vars->size_win_h = 1440;
		if (count_call || *line || !vars->size_win_h || !vars->size_win_w)
			print_error("Error\n : incorrect resolution\n");
		count_call = 1;
		return (1);
	}
	else
		return (0);
}

void		check(int *control, t_vars *vars, char **line, int *i)
{
	static int flag;

	if (*control < 8)
	{
		*control += rgb(*line, vars)
	+ cardinal_points(*line, vars) + resolution(*line, vars);
		(*i)++;
	}
	else if (flag != 1 && **line == '\0')
	{
		(*i)++;
	}
	else
	{
		flag = 1;
		vars->map_h++;
		if (vars->map_w < (int)ft_strlen(*line))
			vars->map_w = ft_strlen(*line);
	}
	free(*line);
}

void		open_file(t_vars *vars, char *file)
{
	int		fd;
	char	*line;
	int		control;
	int		i;

	i = 0;
	control = 0;
	vars->map_h = 0;
	vars->map_w = 0;
	if ((fd = open(file, O_RDONLY)) < 1)
		print_error("Error\n : dont open file");
	while (get_next_line(fd, &line))
	{
		check(&control, vars, &line, &i);
	}
	check(&control, vars, &line, &i);
	if (control < 8)
		print_error("Error\n : not enough information\n");
	close(fd);
	fd = open(file, O_RDONLY);
	get_map(&line, vars, i, fd);
	check_minimap(vars);
}
