/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:37:20 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/19 01:34:33 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		rgb_to_int(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

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

int			cardinal_points(char *line, t_vars *vars)
{
	int i;
	char **path;
	static int enter;
	static int count_call;

	i = 1;
	path = NULL;
	while (ft_isspace(*line))
		line++;
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
	{
		path = &vars->path_tex_wall_no;
		enter = 1;
	}
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
	{
		path = &vars->path_tex_wall_so;
		enter = 2;
	}
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
	{
		path = &vars->path_tex_wall_we;
		enter = 3;
	}
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
	{
		path = &vars->path_tex_wall_ea;
		enter = 4;
	}
	else if (*line == 'S' && *(line + 1) == ' ')
	{
		path = &vars->path_tex_wall_sp;
		enter = 5;
	}
	if (path)
	{
		count_call++;
		line += 2;
		while (ft_isspace(*line))
			line++;
		while (!ft_isspace(*(line + i)) && *(line + i))
			i++;
		if (count_call > 5 || ft_isspace(*(line + i)))
			print_error("ERROR : duplicate path\n");
		else
			*path = line;
	}
	else
		return (0);
	printf("%s\n",*path);
	return (1);
}

int			rgb(char *line, t_vars *vars) {
	int *color;
	int a;
	int b;
	int c;
	static int count_call;
	static int enter;
	color = NULL;
	while (ft_isspace(*line))
		line++;
	if (*line == 'F' && *(line + 1) == ' ') {
		color = &vars->color_floor;
		enter += 2;
	}
	else if (*line == 'C' && *(line + 1) == ' ') {
		color = &vars->color_roof;
		enter += 3;
	}
if (color)
	{
		count_call++;
		line++;
		while (ft_isspace(*line))
			line++;
		a = ft_atoi_cb(&line);
		if (*(line) == ',' && ft_isdigit(*(++line))) {
			b = ft_atoi_cb(&line);
			if (*(line) == ',' && ft_isdigit(*(++line)))
				c = ft_atoi_cb(&line);
			else
				print_error("ERROR : incorrect rgb\n");
			if ((count_call == 2 && enter != 5) || (*line) || a > 255 || b > 255 || c > 255)
				print_error("ERROR : incorrect rgb\n");
		}
		else
			print_error("ERROR : incorrect rgb\n");
		*color = rgb_to_int(a, b, c);
	}
	else
		return (0);
	return (1);
}

void		open_file(t_vars *vars, char *file)
{
	int fd;
	char *line;
	char *line_free;
	int control;
	int i;
	i = -1;
	control = 0;


	fd = open(file, O_RDONLY);
	line_free = line;

	while (get_next_line(fd, &line) && control < 8)
		if (control < 8)
			control += resolution(line, vars) + cardinal_points(line, vars) + rgb(line, vars);
	if (control < 8)
		print_error("ERROR : not enough information\n");
	else
		while (get_next_line(fd, &line))
			reed_map(line, vars);
	free(line);
}
