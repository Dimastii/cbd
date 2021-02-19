/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:33:30 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/19 01:43:15 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int 		check_readability_str_map(const char *line)
{
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == 'N'
		|| *line == 'S' || *line == 'W' || *line == 'E')
			return (1);
		line++;
	}
	return (0);
}

int reed_map(char *line, t_vars *vars)
{
	static int flag;
	static int map_h;

//	printf("%d\n", flag);
	if (flag != 1 && check_readability_str_map(line))
//	if (flag != 1 && !ft_strchr(line, '1') && !ft_strchr(line, '0'))
		return (0);

	if((ft_strchr(line, '1') && ft_strchr(line, '0'))) {
		map_h++;
		flag = 1;
	}

	printf("%s \n", line);
		return (1);

}