/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:56:34 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 22:47:58 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_minimap(t_vars *vars)
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
			check_pers(vars, i, j, &flag);
	}
	if (!flag)
		print_error("player not found");
	map_validator(vars);
}
