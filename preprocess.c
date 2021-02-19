/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:37:20 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/19 20:49:06 by cveeta           ###   ########.fr       */
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
	{
//		free(line);
		return (0);
	}
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
			*path = ft_strdup(line);
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

void		open_file(t_vars *vars, char *file) {
	int fd;
	char *line;
	char *line_free;
	int control;
	int i;
	i = 0;
	control = 0;

	vars->map_h = 0;
	fd = open(file, O_RDONLY);
//	line_free = line;

	while (get_next_line(fd, &line) && control < 8) {
		control += rgb(line, vars) + cardinal_points(line, vars) + resolution(line, vars);
		i++;
		free(line);
	}
	if (control < 8)
		print_error("ERROR : not enough information\n");
	else {
		reed_map(line, vars, 1);
		i++;
		free(line);
		while (get_next_line(fd, &line)) {
			reed_map(line, vars, 1);
			free(line);
		}
	}
	free(line);
	get_next_line(fd, &line);
	reed_map(line, vars, 1);
//	printf("\n%d\n", i);
	free(line);
	close(fd);
	fd = open(file, O_RDONLY);
	while (--i != 0) {
		get_next_line(fd, &line);
//		printf("%s| \n" , line);

		free(line);
	}
	vars->map = malloc(sizeof(char **) * (vars->map_h + 1));
	vars->map[vars->map_h + 1] = NULL;
//	vars->map[i] = ft_strdup(line);
	while (i <= vars->map_h)
	{
		get_next_line(fd, &line);
		vars->map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	for (int j = 0; j <= vars->map_h + 1 ; ++j) {
		printf("%s\n", vars->map[j]);
	}
}
