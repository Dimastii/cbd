/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:33:30 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 19:16:29 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int 		check_readability_str_map(const char *line)
{
	while (*line)
	{
		if (*line == '1' || (*line == '0' || *line == 'N'
		|| *line == 'S' || *line == 'W' || *line == 'E'))
			return (1);
		line++;
	}
	return (0);
}

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