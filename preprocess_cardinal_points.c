/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_cardinal_points.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 23:40:11 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 23:59:16 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		check_id(const char *line, char ***path, t_vars *vars, int *enter)
{
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
	{
		*path = &vars->path_tex_wall_no;
		*enter = 1;
	}
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
	{
		*path = &vars->path_tex_wall_so;
		*enter = 2;
	}
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
	{
		*path = &vars->path_tex_wall_we;
		*enter = 3;
	}
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
	{
		*path = &vars->path_tex_wall_ea;
		*enter = 4;
	}
	else if (*line == 'S' && *(line + 1) == ' ')
	{
		*path = &vars->path_tex_wall_sp;
		*enter = 5;
	}
}

void		skip_line_cp(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

int			cardinal_points(char *line, t_vars *vars)
{
	int			i;
	char		**path;
	static int	enter;
	static int	count_call;

	i = 1;
	path = NULL;
	skip_line_cp(&line);
	check_id(line, &path, vars, &enter);
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
	return (1);
}
