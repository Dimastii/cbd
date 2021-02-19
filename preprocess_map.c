/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:33:30 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/19 20:25:13 by cveeta           ###   ########.fr       */
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

int reed_map(char *line, t_vars *vars, int mode)
{
	static int flag;
	static int local_map_h;

	if (flag != 1 && *line == '\0')
		return (0);
	else if (mode == 1)
	{
		flag = 1;
		vars->map_h++;
	}
	else if (mode == 2)
	{
		vars->map[local_map_h] = ft_strdup(line);

		local_map_h++;
	}
//	printf("%d|%s| \n",map_h , line);


}