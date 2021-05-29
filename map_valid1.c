/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:44:57 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 11:59:47 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_up_bot_left(t_vars *vars, int i, size_t j)
{
	if (i == 0)
		print_error("Error\n : map is not closed.");
	if (j > ft_strlen(vars->map[i - 1]) + 1)
		print_error("Error\n : map is not closed.");
	if (vars->map[i - 1][j - 1])
		if (!ft_strchr("102", vars->map[i - 1][j - 1]))
			print_error("Error\n : map is not closed");
	if (i + 1 < vars->map_h && j > ft_strlen(vars->map[i + 1]) + 1)
		print_error("Error\n : map is not closed.");
	if (i + 1 < vars->map_h && vars->map[i + 1][j - 1])
		if (!ft_strchr("102", vars->map[i + 1][j - 1]))
			print_error("Error\n : map is not closed");
}

void	check_up_bot_middle(t_vars *vars, int i, size_t j)
{
	if (i == 0)
		print_error("Error\n : map is not closed.");
	if (j > ft_strlen(vars->map[i - 1]))
		print_error("Error\n : map is not closed.");
	if (vars->map[i - 1][j])
		if (!ft_strchr("102", vars->map[i - 1][j]))
			print_error("Error\n : map is not closed");
	if (j >= ft_strlen(vars->map[i + 1]))
		print_error("Error\n : map is not closed.");
	if (i + 1 < vars->map_h && vars->map[i + 1][j])
		if (!ft_strchr("102", vars->map[i + 1][j]))
			print_error("Error\n : map is not closed");
}

void	check_up_bot_right(t_vars *vars, int i, size_t j)
{
	if (i == 0)
		print_error("Error\n : map is not closed.");
	if (j >= ft_strlen(vars->map[i - 1]) - 1)
		print_error("Error\n : map is not closed.");
	if (vars->map[i - 1][j + 1])
		if (!ft_strchr("102", vars->map[i - 1][j + 1]))
			print_error("Error\n : map is not closed");
	if (i + 1 < vars->map_h && j >= ft_strlen(vars->map[i + 1]) - 1)
		print_error("Error\n : map is not closed.");
	if (i + 1 < vars->map_h && vars->map[i + 1][j + 1])
		if (!ft_strchr("102", vars->map[i + 1][j + 1]))
			print_error("Error\n : map is not closed");
}

void	check_left_right(t_vars *vars, int i, size_t j)
{
	if (!ft_strchr("102", vars->map[i][j - 1]))
		print_error("Error\n : map is not closed");
	if (vars->map[i][j + 1] != '\0')
	{
		if (!ft_strchr("102", vars->map[i][j + 1]))
			print_error("Error\n : map is not closed");
	}
	else
		print_error("Error\n : map is not closed");
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
