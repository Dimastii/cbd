/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:33:30 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 19:36:20 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int reed_map(char *line, t_vars *vars, int *i)
{
	static int flag;
	static int local_map_h;

	if (flag != 1 && *line == '\0')
	{
		(*i)++;
		return (0);
	}
	else
	{
		flag = 1;
		vars->map_h++;
		if (vars->map_w < ft_strlen(line))
			vars->map_w = ft_strlen(line);
	}
	return (0);
}