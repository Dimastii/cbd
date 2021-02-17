/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 21:40:42 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/17 16:23:07 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub.h"

int worldMap[mapWidth][mapHeight] =
		{//     	   1 2 3 4 5 6 7 8 9 10111231141516171819
		/*0*/		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*2*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*3*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*4*/		{1,0,0,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,0,1},
		/*5*/		{1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
		/*6*/		{1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*7*/		{1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*8*/		{1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*9*/		{1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*11*/		{1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*12*/		{1,0,0,0,9,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
		/*13*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*14*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*15*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*16*/		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		/*1*/		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
//		{
//				{1,1,1,1,1},
//				{1,0,0,0,1},
//				{1,0,9,0,1},
//				{1,0,0,0,1},
//				{1,1,1,1,1},
//		};





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

	step = 0.25;
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
	if (worldMap[(int)vars->x][(int)vars->y] == '0')
	{
		vars->x = pred_x;
		vars->y = pred_y;
	}
}
int				key_release_hook(int keycode, t_vars *vars)
{
	if (keycode == 124)
		vars->button_move = -1;
	else if (keycode == 123)
		vars->button_move = -1;
	else if (keycode == 125)
		vars->button_move = -1;
	else if (keycode == 126)
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

	if (keycode == 124) {
		vars->button_move = 124;
	}
	else if (keycode == 123) {
		vars->button_move = 123;
	}
	else if (keycode == 125) {
		vars->button_move = 125;
	}
	else if (keycode == 126) {
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

void			ft_round(double *cx, double *cy,t_vars *vars)
{
	if (vars->cos_ang > 0 && vars->sin_ang > 0)
	{
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
	}
	else if (vars->cos_ang < 0 && vars->sin_ang > 0)
	{
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx  -1;
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
	}
	else if (vars->cos_ang < 0 && vars->sin_ang < 0)
	{
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx - 1;
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) :*cy + 1;
	}
	else if (vars->cos_ang > 0 && vars->sin_ang < 0)
	{
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) : *cy + 1;
	}
}


int				 game_loop(t_vars* vars)
{
	double cx;
	double cy;
	double cyx;


	double angle_offset = ANLGLE / N_REY;
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
	while (min_angle <= max_angle - angle_offset)
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
		while (cx < mapWidth  && cx > 0)
		{
			ft_round(&cx, &cyx, vars);
			len = fabs((vars->x - cx) / (vars->cos_ang - 0.000000002));
			y = vars->y + (len * (vars->sin_ang * -1));
			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] == 1)
			{
				lenx = len;
				break;
			}
			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] == 9 )
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
		while (cy < mapHeight && cy > 0)
		{
			ft_round(&cyx, &cy, vars);
			len = fabs((vars->y - cy) / (vars->sin_ang - 0.00000002));
			x = vars->x - (len * vars->cos_ang  * - 1);
			if (x < mapWidth && x > 0 && (worldMap[(int)x][(int)cy - vars->no_so] == 1))
			{
				leny = len;
				break;
			}
			if (x < mapWidth && x > 0 && worldMap[(int)x][(int)cy - vars->no_so] == 9)
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
		min_angle += angle_offset;
	}
	if (vars->mode_gl == 2)
	{
		screen(vars);
		exit(0);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int             main(int argc, char **argv)
{
	t_vars      vars;



	if (!ft_strncmp(argv[2], "--save", 6))
		vars.mode_gl = 2;
	else
		vars.mode_gl = 1;
	open_file(&vars, argv[1]);

	vars.x =9.5;
	vars.y =7.5;
	vars.angle_p = -M_PI/8;

	vars.mlx = mlx_init();

	if (vars.mode_gl == 1)
		vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	printf("%p\n", vars.img.addr);
	printf("%p\n", &vars.img);
	vars.img_tex_sp.img = mlx_xpm_file_to_image(vars.mlx, vars.path_tex_wall_sp, &vars.img_tex_sp.w, &vars.img_tex_sp.h);
	vars.img_tex_sp.addr = mlx_get_data_addr(vars.img_tex_sp.img, &vars.img_tex_sp.bits_per_pixel, &vars.img_tex_sp.line_length, &vars.img_tex_sp.endian);


	vars.img_tex_wall_no.img = mlx_xpm_file_to_image(vars.mlx, vars.path_tex_wall_no, &vars.img_tex_wall_no.w, &vars.img_tex_wall_no.h);
	vars.img_tex_wall_no.addr = mlx_get_data_addr(vars.img_tex_wall_no.img, &vars.img_tex_wall_no.bits_per_pixel, &vars.img_tex_wall_no.line_length, &vars.img_tex_wall_no.endian);

	vars.img_tex_wall_so.img = mlx_xpm_file_to_image(vars.mlx, vars.path_tex_wall_so, &vars.img_tex_wall_so.w, &vars.img_tex_wall_so.h);
	vars.img_tex_wall_so.addr = mlx_get_data_addr(vars.img_tex_wall_so.img, &vars.img_tex_wall_so.bits_per_pixel, &vars.img_tex_wall_so.line_length, &vars.img_tex_wall_so.endian);

	vars.img_tex_wall_we.img = mlx_xpm_file_to_image(vars.mlx, vars.path_tex_wall_we, &vars.img_tex_wall_we.w, &vars.img_tex_wall_we.h);
	vars.img_tex_wall_we.addr = mlx_get_data_addr(vars.img_tex_wall_we.img, &vars.img_tex_wall_we.bits_per_pixel, &vars.img_tex_wall_we.line_length, &vars.img_tex_wall_we.endian);

	vars.img_tex_wall_ea.img = mlx_xpm_file_to_image(vars.mlx, vars.path_tex_wall_ea, &vars.img_tex_wall_ea.w, &vars.img_tex_wall_ea.h);
	vars.img_tex_wall_ea.addr = mlx_get_data_addr(vars.img_tex_wall_ea.img, &vars.img_tex_wall_ea.bits_per_pixel, &vars.img_tex_wall_ea.line_length, &vars.img_tex_wall_ea.endian);

	if (vars.mode_gl == 1)
		mlx_hook(vars.win, 2, 1L<<0,key_hook , &vars);
	if (vars.mode_gl == 1)
		mlx_hook(vars.win, 3, 1L<<1,key_release_hook , &vars);
	mlx_loop_hook(vars.mlx, game_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}