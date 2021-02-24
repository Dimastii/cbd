/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:46:00 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 16:55:31 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
			print_error("Error\n : map is not closed");
	}
	if (flag == 1)
		print_error("Error\n : map is not closed");
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
			print_error(
"Error\n : map is not closed. Didnt find start/end of wall");
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
					print_error("Error\n : map is not closed at top");
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
	while (vars->map[++i] && i < vars->map_h)
	{
		j = -1;
		while (vars->map[i][++j] && i < vars->map_h)
			if (vars->map[i][j] == '0' || vars->map[i][j] == '2')
				check_around(vars, i, j);
	}
}

void	check_pers(t_vars *vars, int i, int j, int *flag)
{
	if (vars->map[i][j] == '2')
		vars->n_sprt++;
	if (ft_strchr("SWEN", vars->map[i][j]) && !*flag)
	{
		if (vars->map[i][j] == 'N')
			vars->angle_p = -M_PI / 2;
		if (vars->map[i][j] == 'S')
			vars->angle_p = M_PI / 2;
		if (vars->map[i][j] == 'W')
			vars->angle_p = -M_PI;
		if (vars->map[i][j] == 'E')
			vars->angle_p = 0;
		vars->map[i][j] = '0';
		vars->y = j + .5;
		vars->x = i + .5;
		*flag = 1;
	}
	else if (ft_strchr("SWEN", vars->map[i][j]) && *flag)
		print_error("Error\n : player dup");
}
