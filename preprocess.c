/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:37:20 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 23:49:31 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		print_error(char *mode)
{
	write(2, mode, ft_strlen(mode));
	exit(0);
}

int			resolution(char *line, t_vars *vars)
{
	static int count_call;

	while (*line == ' ')
		line++;
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
			print_error("ERROR : incorrect resolution\n");
		count_call = 1;
		return (1);
	}
	else
		return (0);
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
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) && control < 8)
	{
		control += rgb(line, vars)
				+ cardinal_points(line, vars) + resolution(line, vars);
		i++;
		free(line);
	}
	if (control < 8)
		print_error("ERROR : not enough information\n");
	skip_line(&line, vars, &i, fd);
	fd = open(file, O_RDONLY);
	get_map(&line, vars, &i, fd);
	check_minimap(vars);
}
