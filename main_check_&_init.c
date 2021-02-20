/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check_&_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:09:21 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 20:12:02 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void 		check_argv(t_vars *vars, int argc, char **argv)
{
	vars->angle_p = M_PI /2;
	if (argc == 1)
		print_error("ERROR : incorrect arg\n");
	if (argv[1][ft_strlen(argv[1]) - 1] != 'b'
		&& argv[1][ft_strlen(argv[1]) - 2] != 'u'
		&& argv[1][ft_strlen(argv[1]) - 3] != 'c')
		print_error("ERROR : incorrect .cub\n");
	if (!ft_strncmp(argv[2], "--save", 6))
		vars->mode_gl = 2;
	else
		vars->mode_gl = 1;
}

void		init_win_img_sp(t_vars *vars)
{
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
		print_error("ERROR : incorrect or missing path_tex_wall_sp\n");
}

void		init_no_so(t_vars *vars)
{
	if ((vars->img_tex_wall_no.img = mlx_xpm_file_to_image(vars->mlx,
vars->path_tex_wall_no, &vars->img_tex_wall_no.w, &vars->img_tex_wall_no.h)))
		vars->img_tex_wall_no.addr = mlx_get_data_addr(
vars->img_tex_wall_no.img,
&vars->img_tex_wall_no.bits_per_pixel, &vars->img_tex_wall_no.line_length,
&vars->img_tex_wall_no.endian);
	else
		print_error("ERROR : incorrect or missing path_tex_wall_no\n");
	if ((vars->img_tex_wall_so.img = mlx_xpm_file_to_image(vars->mlx,
vars->path_tex_wall_so, &vars->img_tex_wall_so.w, &vars->img_tex_wall_so.h)))
		vars->img_tex_wall_so.addr = mlx_get_data_addr(
vars->img_tex_wall_so.img, &vars->img_tex_wall_so.bits_per_pixel,
&vars->img_tex_wall_so.line_length, &vars->img_tex_wall_so.endian);
	else
		print_error("ERROR : incorrect or missing path_tex_wall_so\n");
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
		print_error("ERROR : incorrect or missing path_tex_wall_we\n");
	if ((vars->img_tex_wall_ea.img = mlx_xpm_file_to_image(
vars->mlx, vars->path_tex_wall_we, &vars->img_tex_wall_ea.w,
&vars->img_tex_wall_ea.h)))
		vars->img_tex_wall_ea.addr = mlx_get_data_addr(
vars->img_tex_wall_ea.img, &vars->img_tex_wall_ea.bits_per_pixel,
&vars->img_tex_wall_ea.line_length, &vars->img_tex_wall_ea.endian);
	else
		print_error("ERROR : incorrect or missing path_tex_wall_ea\n");
}
void		init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	init_win_img_sp(vars);
	init_no_so(vars);
	init_ea_we(vars);
}
