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
void			  ft_round_angle(double *ang)
{
	if (*ang < 0)
		while (*ang < - (2.0 * M_PI))
			*ang += (2.0 * M_PI);
	else if (*ang > 0)
		while (*ang > (2.0 *  M_PI))
			*ang -= (2.0 * M_PI);
	if (*ang > M_PI) {
		*ang -= (2.0 * M_PI);
	}
	if (*ang < -M_PI) {
		*ang += (2.0 * M_PI);
	}

}
int ft_len_sprt(t_vars *vars, double ang, t_sprite *sprt)
{
	double a1;
	double a2;
	double angle_sptr = -1;
	float h_x;
	double ang_range;

	h_x = sprt->enter_on_len_x - (float)vars->x;

	ang_range = atan(0.5 / sprt->len_to_sprt);

	ft_round_angle(&ang);

	if (sprt->enter_on_len_x - vars->x >= 0 && sprt->enter_on_len_y - vars->y >= 0)
		angle_sptr = -atan((sprt->enter_on_len_y - vars->y) / (h_x));
	else if (sprt->enter_on_len_x - vars->x >= 0 && sprt->enter_on_len_y - vars->y <= 0 )
		angle_sptr = -atan((sprt->enter_on_len_y - vars->y) / (h_x));
	else if (sprt->enter_on_len_x - vars->x <= 0 && sprt->enter_on_len_y - vars->y <= 0)
		angle_sptr = -atan((sprt->enter_on_len_y - vars->y) / (h_x)) + M_PI;
	else if (sprt->enter_on_len_x - vars->x <= 0 && sprt->enter_on_len_y - vars->y >= 0)
		angle_sptr = -atan((sprt->enter_on_len_y - vars->y) / (h_x)) - M_PI;

	a1 = angle_sptr - ang_range;
	a2 = angle_sptr + ang_range;

	if ((ang >= a1 && ang <= a2))
	{
		vars->x_tex_sprt = (ang - a1) / (a2 - a1);
		return (1);
	}
	if (a2 >= M_PI || a1 <= - M_PI) {
		if (sin(ang) >= sin(a2) && sin(ang) <= sin(a1)) {
			if (a2 >= M_PI && ang < 0)
				vars->x_tex_sprt = ((ang + 2 * M_PI) - a1) / (a2 - a1);
			else if (a1 <= - M_PI && ang > 0)
				vars->x_tex_sprt = ((ang - 2 * M_PI) - a1) / (a2 - a1);
			return (1);
		}
	}
	return (0);
}