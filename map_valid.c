/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:56:34 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 19:55:45 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_up_bot_left(t_vars *vars, int i, size_t j)
{
	if (i == 0)
		print_error("map is not closed.");
	if (j > ft_strlen(vars->map[i - 1]) + 1)
		print_error("map is not closed.");
	if (vars->map[i - 1][j - 1])
		if (!ft_strchr("102", vars->map[i - 1][j - 1]))
			print_error("map is not closed");
	if (j > ft_strlen(vars->map[i + 1]) + 1)
		print_error("map is not closed.");
	if (vars->map[i + 1][j - 1])
		if (!ft_strchr("102", vars->map[i + 1][j - 1]))
			print_error("map is not closed");
}

void	check_up_bot_middle(t_vars *vars, int i, size_t j)
{
	if (i == 0)
		print_error("map is not closed.");
	if (j > ft_strlen(vars->map[i - 1]))
		print_error("map is not closed.");
	if (vars->map[i - 1][j])
		if (!ft_strchr("102", vars->map[i - 1][j]))
			print_error("map is not closed");
	if (j >= ft_strlen(vars->map[i + 1]))
		print_error("map is not closed.");
	if (vars->map[i + 1][j])
		if (!ft_strchr("102", vars->map[i + 1][j]))
			print_error("map is not closed");
}

void	check_up_bot_right(t_vars *vars, int i, size_t j)
{
	if (i == 0)
		print_error("map is not closed.");
	if (j >= ft_strlen(vars->map[i - 1]) - 1)
		print_error("map is not closed.");
	if (vars->map[i - 1][j + 1])
		if (!ft_strchr("102", vars->map[i - 1][j + 1]))
			print_error("map is not closed");
	if (j >= ft_strlen(vars->map[i + 1]) - 1)
		print_error("map is not closed.");
	if (vars->map[i + 1][j + 1])
		if (!ft_strchr("102", vars->map[i + 1][j + 1]))
			print_error("map is not closed");
}

void	check_left_right(t_vars *vars, int i, size_t j)
{
	if (!ft_strchr("102", vars->map[i][j - 1]))
		print_error("map is not closed");
	if (vars->map[i][j + 1] != '\0')
	{
		if (!ft_strchr("102", vars->map[i][j + 1]))
			print_error("map is not closed");
	}
	else
		print_error("map is not closed");
}

void	check_around(t_vars *vars, int i, int j)
{
	size_t k;

	k = (size_t)j;
	check_up_bot_left(vars, i, k);
	check_up_bot_middle(vars, i, k);
	check_up_bot_right(vars, i, k);
	check_left_right(vars, i, k);
}


int		check_inside(char *row, int j)
{
	int flag;

	flag = 0;
	while (row[++j])
	{
		if (row[j] == '0')
			flag = 1;
		else if (row[j] == '2')
			;
		else if (row[j] == '1')
		{
			flag = 0;
			break ;
		}
		else if (row[j] == ' ' && flag == 0)
			;
		else
			print_error("map is not closed");
	}
	if (flag == 1)
		print_error("map is not closed");
	return (j - 1);
}

void	check_map_row(t_vars *vars, int i)
{
	int j;

	j = -1;
	while (vars->map[i][++j])
	{
		if (vars->map[i][j] == '1')
			j = check_inside(*(vars->map + i), j);
		else if (!ft_strchr("1 \0", vars->map[i][j]))
			print_error("map is not closed. Didnt find start/end of wall");
	}
}

void	check_close(t_vars *vars)
{
	int	j;
	int i;

	j = -1;
	i = -1;
	while (vars->map[++i] && i < vars->map_h)
	{
		if (i == 0)
		{
			while (vars->map[i][++j])
				if (!ft_strchr("1 \0", vars->map[i][j]))
					print_error("map is not closed at top");
		}
		if (i < vars->map_h)
			check_map_row(vars, i);
	}
}

void	map_validator(t_vars *vars)
{
	int	i;
	int j;

	i = 0;
	check_close(vars);
	while (vars->map[++i] && i < vars->map_h )
	{
		j = -1;
		while (vars->map[i][++j] && i < vars->map_h)
			if (vars->map[i][j] == '0' || vars->map[i][j] == '2')
				check_around(vars, i, j);
	}
}

void	get_minimap(t_vars *vars)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = -1;
	while (++i < vars->map_h)
	{
		j = -1;
		while (++j < vars->map_w)
		{
			if (ft_strchr("SWEN", vars->map[i][j]) && !flag)
			{
				if (vars->map[i][j] == 'N')
					vars->angle_p = - M_PI / 2;
				if (vars->map[i][j] == 'S')
					vars->angle_p = M_PI / 2;
				if (vars->map[i][j] == 'W')
					vars->angle_p = -M_PI;
				if (vars->map[i][j] == 'E')
					vars->angle_p = 0;
				vars->map[i][j] = '0';
				vars->y = j + .5;
				vars->x = i + .5;
				flag = 1;
			}
			else if (ft_strchr("SWEN", vars->map[i][j]) && flag)
				print_error("player dup");
		}
	}
	if (!flag)
		print_error("player not found");
	map_validator(vars);
}