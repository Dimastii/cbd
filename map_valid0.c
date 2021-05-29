/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:56:34 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 16:53:20 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_minimap(t_vars *vars)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = 0;
	while (i < vars->map_h)
	{
		j = 0;
		while (j < vars->map_w)
		{
			check_pers(vars, i, j, &flag);
			j++;
		}
		i++;
	}
	if (!flag)
		print_error("Error\n : player not found");
	map_validator(vars);
}
