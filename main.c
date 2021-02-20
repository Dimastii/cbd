/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 21:40:42 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 20:26:30 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	*(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))) = color;
}

int				my_mlx_pixel_take(t_image data, int x, int y)
{
	return (*(int*)(data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8))));
}

void 			ft_move(t_vars *vars)
{
	double step;
	double turn;

	double pred_x = vars->x;
	double pred_y = vars->y;

	step = 0.2;
	turn = 0.05;
	if (vars->button_rotate == 12) {
		vars->angle_p -= turn;
	}
	else if (vars->button_rotate == 14) {
		vars->angle_p += turn;
	}
	if (vars->button_move == 124) {
		vars->x -= step * sin(vars->angle_p);
		vars->y -= step * cos(vars->angle_p);
	}
	else if (vars->button_move == 123) {
		vars->x += step * sin(vars->angle_p);
		vars->y += step * cos(vars->angle_p);
	}
	else if (vars->button_move == 125) {
		vars->x -= step * cos(vars->angle_p);
		vars->y += step * sin(vars->angle_p);
	}
	else if (vars->button_move == 126) {
		vars->x += step * cos(vars->angle_p);
		vars->y -= step * sin(vars->angle_p);
	}
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

	if (keycode == 2) {
		vars->button_move = 124;
	}
	else if (keycode == 0) {
		vars->button_move = 123;
	}
	else if (keycode == 1) {
		vars->button_move = 125;
	}
	else if (keycode == 13) {
		vars->button_move = 126;
	}
	else {
		vars->button_move = -1;
	}


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

int             main(int argc, char **argv)
{
	t_vars      vars;

	check_argv(&vars, argc, argv);
	open_file(&vars, argv[1]);
	init_mlx(&vars);
	if (vars.mode_gl == 1)
		mlx_hook(vars.win, 2, 1L<<0,key_hook , &vars);
	if (vars.mode_gl == 1)
		mlx_hook(vars.win, 3, 1L<<1,key_release_hook , &vars);
	mlx_loop_hook(vars.mlx, game_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}