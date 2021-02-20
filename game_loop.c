/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:26:33 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 22:17:48 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			while_cx(t_vars *vars, int *n_sprt)
{
	*n_sprt = 0;
	while (vars->lv.cx < MAPH - 1 && vars->lv.cx > 0)
	{
		ft_round(&vars->lv.cx, &vars->lv.cyx, vars);
		vars->lv.len = fabs((vars->x - vars->lv.cx)
				/ (vars->cos_ang - 0.000000002));
		vars->lv.y = vars->y + (vars->lv.len * (vars->sin_ang * -1));
		if (vars->lv.y < MAPW && vars->lv.y > 0 && vars->lv.cx > 0
		&& vars->map[(int)vars->lv.cx - vars->we_ea][(int)vars->lv.y] == '1')
		{
			vars->lv.lenx = vars->lv.len;
			break ;
		}
		while_cx_if_sprt(vars, n_sprt);
	}
}

void			while_cy(t_vars *vars, int *n_sprt)
{
	while (vars->lv.cy < MAPW - 1 && vars->lv.cy > 0)
	{
		ft_round(&vars->lv.cyx, &vars->lv.cy, vars);
		vars->lv.len = fabs((vars->y - vars->lv.cy)
				/ (vars->sin_ang - 0.00000002));
		vars->lv.x = vars->x - (vars->lv.len * vars->cos_ang * -1);
		if (vars->lv.x < MAPH && vars->lv.x > 0
	&& (vars->map[(int)vars->lv.x][(int)vars->lv.cy - vars->no_so] == '1'))
		{
			vars->lv.leny = vars->lv.len;
			break ;
		}
		while_cy_if_sprt(vars, n_sprt);
	}
}

void			preproc_and_render(t_vars *vars, int *num_rey)
{
	if (vars->lv.lenx < vars->lv.leny)
	{
		vars->lv.len = vars->lv.lenx *
				fabs(sin(vars->angle_p + M_PI / 2 - vars->min_angle));
		vars->no_so = -1;
		vars->x_tex = vars->lv.y;
	}
	else
	{
		vars->lv.len = vars->lv.leny *
				fabs(sin(vars->angle_p + M_PI / 2 - vars->min_angle));
		vars->we_ea = -1;
		vars->x_tex = vars->lv.x;
	}
	if (vars->lv.len > 1)
		ft_render_background(*num_rey, vars);
	ft_render_wall(vars, vars->lv.len, *num_rey);
	ft_sort_sprt(vars);
	if (vars->sprite[0].len_to_sprt != -1
	&& vars->lv.len >= vars->sprite[0].len_to_sprt)
		ft_render_sprite(vars, *num_rey, vars->min_angle);
	(*num_rey)++;
	vars->min_angle += ANLGLE / vars->size_win_w;
}

void			cycle(t_vars *vars)
{
	int		i;
	int		num_rey;
	int		n_sprt;

	num_rey = 1;
	while (vars->min_angle <= vars->max_angle - ANLGLE / vars->size_win_w)
	{
		vars->cos_ang = cos(vars->min_angle);
		vars->sin_ang = sin(vars->min_angle);
		i = -1;
		while (++i < vars->n_sprt)
		{
			vars->sprite[i].create = -1;
			vars->sprite[i].len_to_sprt = -1.0;
		}
		vars->no_so = (vars->sin_ang > 0) ? 1 : 0;
		vars->we_ea = (vars->cos_ang < 0) ? 1 : 0;
		vars->lv.cx = vars->x;
		vars->lv.cy = vars->y;
		vars->lv.lenx = 10000000000;
		vars->lv.leny = 10000000000;
		while_cx(vars, &n_sprt);
		while_cy(vars, &n_sprt);
		preproc_and_render(vars, &num_rey);
	}
}

int				game_loop(t_vars *vars)
{
	vars->max_angle = vars->angle_p + ANLGLE / 2.0;
	vars->min_angle = vars->angle_p - ANLGLE / 2.0;
	if (vars->mode_gl == 1)
		mlx_clear_window(vars->mlx, vars->win);
	if (vars->mode_gl == 1)
		mlx_sync(1, vars->img.img);
	ft_move(vars);
	cycle(vars);
	if (vars->mode_gl == 2)
	{
		screenshot(vars);
		exit(0);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
