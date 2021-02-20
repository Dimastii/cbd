/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:04:08 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 00:02:18 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	screenshot_norm_two(int fd, int all_pix, int zero, int size)
{
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

static	void	screenshot_norm_one(int fd)
{
	short	plane;

	plane = 1;
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void			fill_screen(int fd, t_vars *vars)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < vars->size_win_h)
	{
		j = 0;
		while (j < vars->size_win_w)
		{
			color = my_mlx_pixel_take((vars->img), j, vars->size_win_h - 1 - i);
			write(fd, &color, 4);
			j++;
		}
		i++;
	}
}

void			screenshot(t_vars *vars)
{
	int		fd;
	int		all_pix;
	int		zero;
	int		pos_pix;
	int		size;

	fd = open("screen.bmp", O_CREAT | O_WRONLY, 0777);
	all_pix = vars->size_win_w * vars->size_win_h * 4 + 54;
	zero = 0;
	pos_pix = 54;
	size = vars->size_win_w * vars->size_win_h;
	write(fd, "BM", 2);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pix, 4);
	pos_pix = 40;
	write(fd, &pos_pix, 4);
	write(fd, &vars->size_win_w, 4);
	write(fd, &vars->size_win_h, 4);
	screenshot_norm_one(fd);
	screenshot_norm_two(fd, all_pix, zero, size);
	fill_screen(fd, vars);
}
