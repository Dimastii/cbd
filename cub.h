/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:59:11 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 21:43:54 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB_H
# define CUB3D_CUB_H
# include <stdio.h>
# include "libft/libft.h"
# include <math.h>
# include "mlx.h"
# include "fcntl.h"
# include "unistd.h"
# include <string.h>
# include <stdlib.h>

# define ANLGLE M_PI / 4

typedef struct	s_image {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			w;
	int			h;
}				t_image;

typedef struct	s_sprite {
	double		len_to_sprt;

	double		enter_on_len_x;
	double		enter_on_len_y;

	int			create;

}				t_sprite;
typedef struct	s_loop_var {
	double		cy;
	double		cx;
	double		cyx;
	double		lenx;
	double		leny;
	double		len;
	double		y;
	double		x;
}				t_loop_var;

typedef struct	s_clr {
	int		a;
	int		b;
	int		c;
}				t_clr;

typedef struct	s_vars {
	char		**map;
	void		*mlx;
	void		*win;
	t_loop_var	lv;
	double		max_angle;
	double		y;
	double		min_angle;
	double		x;
	double		angle_p;
	double		x_tex;
	double		x_tex_sprt;
	double		cos_ang;
	double		sin_ang;
	t_sprite	*sprite;
	t_image		img;
	t_image		img_tex_wall_no;
	t_image		img_tex_wall_so;
	t_image		img_tex_wall_we;
	t_image		img_tex_wall_ea;
	t_image		img_tex_sp;
	t_image		img_tex_print;
	int			map_h;
	int			map_w;
	int			size_win_w;
	int			color_floor;
	int			color_roof;
	int			button_rotate;
	int			button_move;
	int			mode_gl;
	int			size_win_h;
	int			no_so;
	int			we_ea;
	int			n_sprt;
	char		*path_tex_wall_no;
	char		*path_tex_wall_we;
	char		*path_tex_wall_so;
	char		*path_tex_wall_ea;
	char		*path_tex_wall_sp;
}				t_vars;

void			ft_round(double *cx, double *cy, t_vars *vars);
void			ft_render_background(int num_rey, t_vars *vars);
void			ft_print_wall_sprite(t_vars *vars, double len_r, int num_rey);
void			ft_render_sprite(t_vars *vars, int num_rey, double min_angle);
void			ft_round_sprt_x(double angl, double *x, double *y);
void			ft_round_sprt_y(double angl, double *x, double *y);
void			ft_sort_sprt(t_vars *vars);
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);
void			ft_render_wall(t_vars *vars, double len_r_norm, int num);
void			ft_round_angle(double *ang);
void			screenshot(t_vars *vars);
void			print_error(char *mode);
void			open_file(t_vars *vars, char *file);
void			init_mlx(t_vars *vars);
void			ft_move(t_vars *vars);
void			while_cy_if_sprt(t_vars *vars, int *n_sprt);
void			map_validator(t_vars *vars);
void			check_minimap(t_vars *vars);
void			while_cx_if_sprt(t_vars *vars, int *n_sprt);
void			check_around(t_vars *vars, int i, int j);
void			check_pers(t_vars *vars, int i, int j, int *flag);
void			check_argv(t_vars *vars, int argc, char **argv);
void			skip_line(char **line, t_vars *vars, int *i, int fd);
void			get_map(char **line, t_vars *vars, int i, int fd);
char			*ft_strdup_cd(const char *s, int len);
int				game_loop(t_vars *vars);
int				ft_len_sprt(t_vars *vars, double ang, t_sprite *sprt);
int				ft_exit();
int				my_mlx_pixel_take(t_image data, int x, int y);
int				ft_atoi_cb(char **str);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				get_next_line(int fd, char **line);
int				reed_map(char *line, t_vars *vars, int *i);
int				key_hook(int keycode, t_vars *vars);
int				key_release_hook(int keycode, t_vars *vars);
int				rgb_to_int(int r, int g, int b);
int				rgb(char *line, t_vars *vars);
int				cardinal_points(char *line, t_vars *vars);
int				mlx_sync(int cmd, void *param);
#endif
