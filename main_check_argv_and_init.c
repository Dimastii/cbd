/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check_argv_and_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:09:21 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/21 18:46:33 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		check_argv(t_vars *vars, int argc, char **argv)
{
	vars->angle_p = M_PI / 2;
	if (argc == 1 || argc > 3)
		print_error("Error\n : incorrect arg\n");
	if (ft_strlen(argv[1]) < 4 || argv[1][ft_strlen(argv[1]) - 1] != 'b'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u'
		|| argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 4] != '.')
		print_error("Error\n : incorrect .cub\n");
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
	{
		vars->mode_gl = 2;
		return ;
	}
	else if (argc == 3)
		print_error("Error\n : incorrect arg\n");
	vars->mode_gl = 1;
}

void		init_win_img_sp(t_vars *vars)
{
	if (vars->path_tex_wall_sp[ft_strlen(vars->path_tex_wall_sp) - 1] != 'm'
	|| vars->path_tex_wall_sp[ft_strlen(vars->path_tex_wall_sp) - 2] != 'p'
	|| vars->path_tex_wall_sp[ft_strlen(vars->path_tex_wall_sp) - 3] != 'x'
	|| vars->path_tex_wall_sp[ft_strlen(vars->path_tex_wall_sp) - 4] != '.')
		print_error("Error : \n file no xpm");
	if (vars->mode_gl == 1)
		vars->win = mlx_new_window(vars->mlx,
vars->size_win_w, vars->size_win_h, "Gucci flip flops");
	vars->img.img = mlx_new_image(vars->mlx,
vars->size_win_w, vars->size_win_h);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	if ((vars->img_tex_sp.img = mlx_xpm_file_to_image(vars->mlx,
vars->path_tex_wall_sp, &vars->img_tex_sp.w, &vars->img_tex_sp.h)))
		vars->img_tex_sp.addr = mlx_get_data_addr(vars->img_tex_sp.img,
&vars->img_tex_sp.bits_per_pixel, &vars->img_tex_sp.line_length,
&vars->img_tex_sp.endian);
	else
		print_error("Error\n : incorrect or missing path_tex_wall_sp\n");
}

void		init_no_so(t_vars *vars)
{
	if (vars->path_tex_wall_no[ft_strlen(vars->path_tex_wall_no) - 1] != 'm'
	|| vars->path_tex_wall_no[ft_strlen(vars->path_tex_wall_no) - 2] != 'p'
	|| vars->path_tex_wall_no[ft_strlen(vars->path_tex_wall_no) - 3] != 'x'
	|| vars->path_tex_wall_no[ft_strlen(vars->path_tex_wall_no) - 4] != '.')
		print_error("Error : \n no file no xpm");
	if ((vars->img_tex_wall_no.img = mlx_xpm_file_to_image(vars->mlx,
vars->path_tex_wall_no, &vars->img_tex_wall_no.w, &vars->img_tex_wall_no.h)))
		vars->img_tex_wall_no.addr = mlx_get_data_addr(
vars->img_tex_wall_no.img,
&vars->img_tex_wall_no.bits_per_pixel, &vars->img_tex_wall_no.line_length,
&vars->img_tex_wall_no.endian);
	else
		print_error("Error\n : incorrect or missing path_tex_wall_no\n");
	if ((vars->img_tex_wall_so.img = mlx_xpm_file_to_image(vars->mlx,
vars->path_tex_wall_so, &vars->img_tex_wall_so.w, &vars->img_tex_wall_so.h)))
		vars->img_tex_wall_so.addr = mlx_get_data_addr(
vars->img_tex_wall_so.img, &vars->img_tex_wall_so.bits_per_pixel,
&vars->img_tex_wall_so.line_length, &vars->img_tex_wall_so.endian);
	else
		print_error("Error\n : incorrect or missing path_tex_wall_so\n");
}

void		init_ea_we(t_vars *vars)
{
	if ((vars->img_tex_wall_we.img = mlx_xpm_file_to_image(
vars->mlx, vars->path_tex_wall_ea, &vars->img_tex_wall_we.w,
&vars->img_tex_wall_we.h)))
		vars->img_tex_wall_we.addr = mlx_get_data_addr(
vars->img_tex_wall_we.img, &vars->img_tex_wall_we.bits_per_pixel,
&vars->img_tex_wall_we.line_length, &vars->img_tex_wall_we.endian);
	else
		print_error("Error\n : incorrect or missing path_tex_wall_we\n");
	if ((vars->img_tex_wall_ea.img = mlx_xpm_file_to_image(
vars->mlx, vars->path_tex_wall_we, &vars->img_tex_wall_ea.w,
&vars->img_tex_wall_ea.h)))
		vars->img_tex_wall_ea.addr = mlx_get_data_addr(
vars->img_tex_wall_ea.img, &vars->img_tex_wall_ea.bits_per_pixel,
&vars->img_tex_wall_ea.line_length, &vars->img_tex_wall_ea.endian);
	else
		print_error("Error\n : incorrect or missing path_tex_wall_ea\n");
}

void		init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->max_angle = vars->angle_p + ANLGLE / 2.0;
	vars->min_angle = vars->angle_p - ANLGLE / 2.0;
	vars->sprite = malloc(sizeof(t_sprite) * vars->n_sprt);
	if (vars->path_tex_wall_so[ft_strlen(vars->path_tex_wall_so) - 1] != 'm'
	|| vars->path_tex_wall_so[ft_strlen(vars->path_tex_wall_so) - 2] != 'p'
	|| vars->path_tex_wall_so[ft_strlen(vars->path_tex_wall_so) - 3] != 'x'
	|| vars->path_tex_wall_so[ft_strlen(vars->path_tex_wall_so) - 4] != '.')
		print_error("Error : \n so file no xpm");
	if (vars->path_tex_wall_we[ft_strlen(vars->path_tex_wall_we) - 1] != 'm'
	|| vars->path_tex_wall_we[ft_strlen(vars->path_tex_wall_we) - 2] != 'p'
	|| vars->path_tex_wall_we[ft_strlen(vars->path_tex_wall_we) - 3] != 'x'
	|| vars->path_tex_wall_we[ft_strlen(vars->path_tex_wall_we) - 4] != '.')
		print_error("Error : \n we file no xpm");
	if (vars->path_tex_wall_ea[ft_strlen(vars->path_tex_wall_ea) - 1] != 'm'
	|| vars->path_tex_wall_ea[ft_strlen(vars->path_tex_wall_ea) - 2] != 'p'
	|| vars->path_tex_wall_ea[ft_strlen(vars->path_tex_wall_ea) - 3] != 'x'
	|| vars->path_tex_wall_ea[ft_strlen(vars->path_tex_wall_ea) - 4] != '.')
		print_error("Error : \n ea file no xpm");
	init_win_img_sp(vars);
	init_no_so(vars);
	init_ea_we(vars);
}
