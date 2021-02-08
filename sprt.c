/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:58:40 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/08 20:41:32 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

///unsigned int yyy = 0xDC143C;
void	ft_print_wall_sprite(t_vars *vars, double len_r, int num_rey, double min_angle)
{
//	double wall_h = vars->size_win_h / (len_r);
//	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
//	int drawend = wall_h / 2 + vars->size_win_h / 2;
//	if (drawStart <0) drawStart = 0;
//	if (drawend >= vars->size_win_h) drawend = vars->size_win_h - 1;
//	int color;
//
//	wall_h = drawStart;
//
//	while (wall_h < drawend)
//	{
//		color = my_mlx_pixel_take(vars->img_tex_sp, (num_rey - 1) % 64, wall_h);
//		my_mlx_pixel_put(&vars->img, num_rey - 1 ,wall_h, color);
//		wall_h++;
//	}
	int wall_y;
	double wall_h = vars->size_win_h / len_r;
	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
	int drawend = wall_h / 2 + vars->size_win_h / 2;
	int wall_y1 = drawStart;
	int color = 1111111;
	int y;


	wall_y = 0;
	while (wall_y1 < drawend)
	{
		y = (int)(((float)(wall_y1 - drawStart) /((float)drawend - (float)drawStart)) * 700.0);
		//color = my_mlx_pixel_take(vars->img_tex_sp,(int)((vars->x_tex - (int)vars->x_tex) * 700.0), y);
		if (wall_y1 >= 0 && wall_y1 < vars->size_win_h)
			my_mlx_pixel_put(&vars->img, num_rey - 1 ,wall_y1, vars->color);

		wall_y1++;
		wall_y++;
	}
}

void	ft_render_sprite(t_vars *vars , int num_rey, double min_angle)
{
	int i;

	i = 0;
	while (vars->sprite[i].create != -1) {
		i++;
	}

	while (i--)
	{
		//vars->sprite[i].cord.num++;
		if (ft_len_sprt(vars, min_angle, &vars->sprite[i]))
			ft_print_wall_sprite(vars,vars->sprite[i].cord.len_to_sprt, num_rey, min_angle);
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
	float temp;
	while (vars->sprite[i].create != -1)
	{
		j = i + 1;
		while (vars->sprite[j].create != -1)
		{
			if (vars->sprite[j].cord.len_to_sprt < vars->sprite[i].cord.len_to_sprt)
			{
				temp = vars->sprite[j].cord.len_to_sprt;
				vars->sprite[j].cord.len_to_sprt = vars->sprite[i].cord.len_to_sprt;
				vars->sprite[i].cord.len_to_sprt = temp;
			}
			j++;
		}
		i++;
	}
}