/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:37:20 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/17 15:43:55 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		rgb_to_int(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int		int_to_rgb(t_rgb *clr, int color)
{
	clr->r = color >> 16;
	clr->g = color >> 8;
	clr->b = color;
	//return(r << 16 | g << 8 | b);
}

void		print_error(int mode)
{
	if (mode == 1)
		printf("ERROR : incorrect resolution\n");
	if (mode == 2)
		printf("ERROR : incorrect path\n");
	if (mode == 3)
		printf("ERROR : incorrect rgb\n");
	exit(0);
}

int			resolution(char *line, t_vars *vars)
{
	while (*line == ' ')
		line++;
	if (*line == 'R')
	{
		line++;
		vars->size_win_w = ft_atoi(&line);
		vars->size_win_h = ft_atoi(&line);
		if (vars->size_win_w > 2560 && vars->mode_gl == 1)
			vars->size_win_w = 2560;
		if (vars->size_win_h > 1440 && vars->mode_gl == 1)
			vars->size_win_h = 1440;
		if (*line || !vars->size_win_h || !vars->size_win_w)
			print_error(1);
		return 0;
	}
	else
		return (1);

}

int			cardinal_points(char *line, t_vars *vars)
{
	int i;
	char **path;
	i = 1;

	path = NULL;
	while (ft_isspace(*line))
		line++;
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		path = &vars->path_tex_wall_no;
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		path = &vars->path_tex_wall_so;
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		path = &vars->path_tex_wall_we;
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		path = &vars->path_tex_wall_ea;
	else if (*line == 'S' && *(line + 1) == ' ')
		path = &vars->path_tex_wall_sp;
	if (path)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		while (!ft_isspace(*(line + i)) && *(line + i))
			i++;
		if (ft_isspace(*(line + i)))
			print_error(2);
		else
			*path = line;
	}
	else
		return (1);
	printf("%s\n",*path);
	return (0);
}

int			rgb(char *line, t_vars *vars)
{
	int *color;
	int a;
	int b;
	int c;

	color = NULL;
	while (ft_isspace(*line))
		line++;
	if (*line == 'F' && *(line + 1) == ' ')
		color = &vars->color_floor;
	else if (*line == 'C' && *(line + 1) == ' ')
		color = &vars->color_roof;
	if (color)
	{
		line++;
		while (ft_isspace(*line))
			line++;
		a = ft_atoi(&line);
		if (*(line) == ',' && ft_isdigit(*(++line))) {
			b = ft_atoi(&line);
			if (*(line) == ',' && ft_isdigit(*(++line)))
				c = ft_atoi(&line);
			else
				print_error(3);
			if ((*line) || a > 255 || b > 255 || c > 255)
				print_error(3);
		}
		else
			print_error(3);
		*color = rgb_to_int(a, b, c);
	}
	else
		return (1);
	return (0);
}

void		open_file(t_vars *vars, char *file)
{
	int fd;
	char *line;
	char *line_free;

	line_free = line;
	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	resolution(line, vars);
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	cardinal_points(line, vars);
	get_next_line(fd, &line);
	cardinal_points(line, vars);
	get_next_line(fd, &line);
	cardinal_points(line, vars);
	get_next_line(fd, &line);
	cardinal_points(line, vars);
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	cardinal_points(line, vars);
	get_next_line(fd, &line);
	rgb(line, vars);
	get_next_line(fd, &line);
	rgb(line, vars);
}
