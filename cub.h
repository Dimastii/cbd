/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:59:11 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/18 12:31:49 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB_H
#define CUB3D_CUB_H
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "unistd.h"
#include "get_next_line.h"
#include <string.h>

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

typedef struct  s_sprite {
	double len_to_sprt;

	double enter_on_len_x;
	double enter_on_len_y;

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

	t_sprite sprite[100];

	t_image 		img;

	t_image		img_tex_wall_no;
	char		*path_tex_wall_no;
	t_image		img_tex_wall_so;
	char		*path_tex_wall_so;
	t_image		img_tex_wall_we;
	char		*path_tex_wall_we;
	t_image		img_tex_wall_ea;
	char		*path_tex_wall_ea;
	t_image		img_tex_sp;
	char		*path_tex_wall_sp;
	t_image		img_tex_print;


	double x_tex;
	double x_tex_sprt;

	int color_floor;
	int color_roof;

	double cos_ang;
	double sin_ang;

	int		button_rotate;
	int		button_move;

	int mode_gl;
}               t_vars;

void			ft_round(double *cx, double *cy,t_vars *vars);
void			ft_render_background(int num_rey, t_vars *vars);
void			ft_print_wall_sprite(t_vars *vars, double len_r,int num_rey);
void			ft_render_sprite(t_vars *vars , int num_rey, double min_angle);
void			ft_round_sprt_x(double angl,double *x, double *y);
void			ft_round_sprt_y(double angl,double *x, double *y);
void			ft_sort_sprt(t_vars *vars );
void			my_mlx_pixel_put(t_image *data,int x,int y,int color);
void			ft_render_wall(t_vars *vars, double len_r_norm, int num);
void			ft_round_angle(double *ang);
void			open_file(t_vars *vars, char *file);
int				game_loop(t_vars* vars);
int				ft_len_sprt(t_vars *vars, double ang, t_sprite *sprt);
int				my_mlx_pixel_take(t_image data,int x,int y);
int				ft_atoi(char **str);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			screenshot(t_vars *vars);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *string, int symbol);
char				*ft_strjoin(char const *s1, char const *s2);
int					get_next_line(int fd, char **line);
char				*ft_strdup(const char *s);
size_t				ft_strlcpy(char *dst, const char *src);
void			print_error(int mode);

#endif
