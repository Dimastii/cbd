/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 23:22:30 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 11:59:47 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		pars_rgb(int *count_call, int enter, int **color, char **line)
{
	t_clr clr;

	(*count_call)++;
	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	clr.a = ft_atoi_cb(line);
	if (**(line) == ',' && ft_isdigit(*(++(*line))))
	{
		clr.b = ft_atoi_cb(line);
		if (**(line) == ',' && ft_isdigit(*(++(*line))))
			clr.c = ft_atoi_cb(line);
		else
			print_error("Error\n : incorrect rgb\n");
		if ((*count_call == 2 && enter != 5) || (**line)
		|| clr.a > 255 || clr.b > 255 || clr.c > 255)
			print_error("Error\n : incorrect rgb\n");
	}
	else
		print_error("Error\n : incorrect rgb\n");
	**color = rgb_to_int(clr.a, clr.b, clr.c);
}

int			rgb(char *line, t_vars *vars)
{
	int			*color;
	static int	count_call;
	static int	enter;

	color = NULL;
	if (*line == 'F' && *(line + 1) == ' ')
	{
		color = &vars->color_floor;
		enter += 2;
	}
	else if (*line == 'C' && *(line + 1) == ' ')
	{
		color = &vars->color_roof;
		enter += 3;
	}
	if (color)
	{
		pars_rgb(&count_call, enter, &color, &line);
	}
	else
		return (0);
	return (1);
}
