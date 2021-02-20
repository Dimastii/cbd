/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:24:58 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 22:29:51 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			button_move(t_vars *vars, double step)
{
	if (vars->button_move == 124)
	{
		vars->x -= step * sin(vars->angle_p);
		vars->y -= step * cos(vars->angle_p);
	}
	else if (vars->button_move == 123)
	{
		vars->x += step * sin(vars->angle_p);
		vars->y += step * cos(vars->angle_p);
	}
	else if (vars->button_move == 125)
	{
		vars->x -= step * cos(vars->angle_p);
		vars->y += step * sin(vars->angle_p);
	}
	else if (vars->button_move == 126)
	{
		vars->x += step * cos(vars->angle_p);
		vars->y -= step * sin(vars->angle_p);
	}
}

void			ft_move(t_vars *vars)
{
	double step;
	double turn;
	double pred_x;
	double pred_y;

	pred_x = vars->x;
	pred_y = vars->y;
	step = 0.2;
	turn = 0.05;
	if (vars->button_rotate == 12)
		vars->angle_p -= turn;
	else if (vars->button_rotate == 14)
		vars->angle_p += turn;
	button_move(vars, step);
	if (vars->map[(int)(vars->x)][(int)(vars->y)] == '1')
	{
		vars->x = pred_x;
		vars->y = pred_y;
	}
}

int				key_release_hook(int keycode, t_vars *vars)
{
	if (keycode == 2)
		vars->button_move = -1;
	else if (keycode == 0)
		vars->button_move = -1;
	else if (keycode == 1)
		vars->button_move = -1;
	else if (keycode == 13)
		vars->button_move = -1;
	if (keycode == 12)
		vars->button_rotate = -1;
	else if (keycode == 14)
		vars->button_rotate = -1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int				key_hook(int keycode, t_vars *vars)
{
	if (keycode == 2)
		vars->button_move = 124;
	else if (keycode == 0)
		vars->button_move = 123;
	else if (keycode == 1)
		vars->button_move = 125;
	else if (keycode == 13)
		vars->button_move = 126;
	else
		vars->button_move = -1;
	if (keycode == 12)
		vars->button_rotate = 12;
	else if (keycode == 14)
		vars->button_rotate = 14;
	else
		vars->button_rotate = -1;
	if (keycode == 53)
		exit(0);
	return (0);
}
