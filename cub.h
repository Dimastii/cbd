/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:59:11 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/08 20:26:40 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB_H
#define CUB3D_CUB_H
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

#define mapWidth  24
#define mapHeight 24

#define ANLGLE M_PI / 4
#define N_REY vars->size_win_w

typedef struct  s_image {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int 		w;
	int 		h;
}               t_image;

typedef struct  s_sprite_cord {

	float enter_on_len_x;
	float enter_on_leny_y;
	float enter_on_lenx_x;
	float enter_on_lenx_y;
	int num;
	float len_to_sprt;


}               t_sprite_cord;

typedef struct  s_sprite {
	int offset_mode_cord_sprite_x;
	int offset_mode_cord_sprite_y;

	t_sprite_cord cord;

	float enter_on_len_x;
	float enter_on_len_y;


	int create;
}               t_sprite;

typedef struct  s_vars {
	void        *mlx;
	void        *win;

	int size_win_w;
	int size_win_h;

	double x;
	double y;
	double angle_p;

	int no_so;
	int we_ea;
	unsigned long color;

	t_sprite sprite[100];

	t_image 		img;
	t_image		img_tex;
	t_image		img_tex_sp;
	double x_tex;
	double y_tex;
}               t_vars;


void rey(t_vars* vars);
int ft_len_sprt(t_vars *vars, double ang, t_sprite *sprt);

void	ft_print_wall_sprite(t_vars *vars, double len_r, int num_rey, double min_angle);
void	ft_render_sprite(t_vars *vars , int num_rey, double min_angle);
void ft_round_sprt_x(double angl, float *x, float *y);
void ft_round_sprt_y(double angl, float *x, float *y);
void ft_sort_sprt(t_vars *vars );
void            my_mlx_pixel_put(t_image *data, int x, int y, int color);
int            my_mlx_pixel_take(t_image data, int x, int y);
#endif //CUB3D_CUB_H
