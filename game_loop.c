/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:26:33 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 20:28:00 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				 game_loop(t_vars* vars)
{
	double cx;
	double cy;
	double cyx;

	double max_angle = vars->angle_p + ANLGLE / 2.0;
	double min_angle = vars->angle_p - ANLGLE / 2.0;

	int num_rey = 1;

	int	n_sprt;

	double lenx;
	double leny;
	double len;
	double y;
	double x;


	int i;

	if (vars->mode_gl == 1)
		mlx_clear_window(vars->mlx, vars->win);
	if (vars->mode_gl == 1)
		mlx_sync(1, vars->img.img);
	ft_move(vars);
	while (min_angle <= max_angle - ANLGLE / vars->size_win_w)
	{
		vars->cos_ang = cos(min_angle);
		vars->sin_ang = sin(min_angle);
		i = -1;
		while (++i < 100)
		{
			vars->sprite[i].create = -1;
			vars->sprite[i].len_to_sprt = -1.0;
		}
		vars->no_so = (vars->sin_ang > 0) ?  1 : 0;
		vars->we_ea = (vars->cos_ang < 0) ?  1 : 0;
		cx = vars->x;
		cy = vars->y;

		lenx = 10000000000;
		leny = 10000000000;

		n_sprt = 0;
		while (cx < MAPH - 1 && cx > 0)
		{
			ft_round(&cx, &cyx, vars);
			len = fabs((vars->x - cx) / (vars->cos_ang - 0.000000002));
			y = vars->y + (len * (vars->sin_ang * -1));
			if (y < MAPW && y > 0 && cx > 0 && vars->map[(int)cx - vars->we_ea][(int)y] == '1')
			{
				lenx = len;
				break;
			}
			if (y < MAPW && y > 0 && cx > 0 && vars->map[(int)cx - vars->we_ea][(int)y] == '2' )
			{
				if (vars->sprite[n_sprt].len_to_sprt == -1) {

					vars->sprite[n_sprt].enter_on_len_x = cx;
					vars->sprite[n_sprt].enter_on_len_y = y;

					ft_round_sprt_x(min_angle, &vars->sprite[n_sprt].enter_on_len_x,
									&vars->sprite[n_sprt].enter_on_len_y);
					vars->sprite[n_sprt].len_to_sprt = sqrt(
							pow(vars->sprite[n_sprt].enter_on_len_x - vars->x, 2) +
							pow(vars->sprite[n_sprt].enter_on_len_y - vars->y, 2));
					vars->sprite[n_sprt].create = 1;

					n_sprt++;
				}
			}
		}
		while (cy < MAPW - 1 && cy > 0)
		{
			ft_round(&cyx, &cy, vars);
			len = fabs((vars->y - cy) / (vars->sin_ang - 0.00000002));
			x = vars->x - (len * vars->cos_ang  * - 1);
			if (x < MAPH && x > 0 && (vars->map[(int)x][(int)cy - vars->no_so] == '1'))
			{
				leny = len;
				break;
			}
			if (x < MAPH && x > 0 && vars->map[(int)x][(int)cy - vars->no_so] == '2')
			{
				if (vars->sprite[n_sprt].len_to_sprt == -1) {
					vars->sprite[n_sprt].enter_on_len_x = x;
					vars->sprite[n_sprt].enter_on_len_y = cy;

					ft_round_sprt_y(min_angle, &vars->sprite[n_sprt].enter_on_len_x,
									&vars->sprite[n_sprt].enter_on_len_y);
					vars->sprite[n_sprt].len_to_sprt = sqrt(
							pow(vars->sprite[n_sprt].enter_on_len_x - vars->x, 2) +
							pow(vars->sprite[n_sprt].enter_on_len_y - vars->y, 2));
					vars->sprite[n_sprt].create = 1;
					n_sprt++;
				}
			}
		}


		if (lenx < leny)
		{
			len = lenx * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
			vars->no_so = -1;
			vars->x_tex = y;
		}
		else
		{
			len = leny * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
			vars->we_ea = -1;
			vars->x_tex = x;
		}
		if (len > 1)
			ft_render_background(num_rey, vars);
		ft_render_wall(vars, len, num_rey);
		ft_sort_sprt(vars);
		if (vars->sprite[0].len_to_sprt != -1 && len >= vars->sprite[0].len_to_sprt)
			ft_render_sprite(vars, num_rey, min_angle);
		num_rey++;
		min_angle += ANLGLE / vars->size_win_w;
	}
	if (vars->mode_gl == 2)
	{
		screenshot(vars);
		exit(0);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);

	return (0);
}