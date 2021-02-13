/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:58:40 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/12 21:52:39 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_print_wall_sprite(t_vars *vars, double len_r, int num_rey, int clr)
{
	int wall_y;
	double wall_h = vars->size_win_h / len_r;
	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
	int drawend = wall_h / 2 + vars->size_win_h / 2;
	int wall_y1 = drawStart;
	int color;
	int y;

	vars->img_tex_print.h = vars->img_tex_sp.h;
	vars->img_tex_print.w = vars->img_tex_sp.w;
	vars->img_tex_print = vars->img_tex_sp;
	wall_y = 0;
	while (wall_y1 < drawend)
	{
		y = (int)(((float)(wall_y1 - drawStart) /((float)drawend - (float)drawStart)) * (float)vars->img_tex_print.h);
		color = my_mlx_pixel_take(vars->img_tex_print, (int)(vars->x_tex_sprt * vars->img_tex_print.w), y);
		if (wall_y1 >= 0 && wall_y1 < vars->size_win_h && color > 0)
			my_mlx_pixel_put(&vars->img, num_rey - 1 ,wall_y1, color);
		wall_y1++;
		wall_y++;
	}
}

void	ft_render_sprite(t_vars *vars , int num_rey, double min_angle)
{
	int i;

	i = 0;
	while (vars->sprite[i].create != -1)
		i++;
	while (i) {
		i--;
		if (ft_len_sprt(vars, min_angle, &vars->sprite[i]))
			ft_print_wall_sprite(vars, vars->sprite[i].len_to_sprt, num_rey, vars->sprite[i].clr);
	}
}


void ft_round_sprt_x(double angl, float *x, float *y)
{
	if (cos(angl) < 0)
	{
		*y = ceilf(*y) - (float)0.5;
		*x -= (float)0.5;
	}
	else if (cos(angl) > 0)
	{
		*y = ceilf(*y) - (float)0.5;
		*x += (float)0.5;
	}
}

void ft_round_sprt_y(double angl, float *x, float *y)
{
	if (sin(angl) < 0)
	{
		*x = ceilf(*x) - (float)0.5;
		*y += (float)0.5;
	}
	else if (sin(angl) > 0)
	{
		*x = ceilf(*x) - (float)0.5;
		*y -= (float)0.5;
	}
}
void ft_sort_sprt(t_vars *vars )
{
	int i = 0;
	int j;
	t_sprite temp;
	while (vars->sprite[i].create != -1)
	{
		j = i + 1;
		while (vars->sprite[j].create != -1)
		{
			if (vars->sprite[j].len_to_sprt < vars->sprite[i].len_to_sprt)
			{
				temp = vars->sprite[j];
				vars->sprite[j] = vars->sprite[i];
				vars->sprite[i] =  temp;
			}
			j++;
		}
		i++;
	}
}