/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:03:08 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/15 21:44:29 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			ft_render_background(int num_rey, t_vars *vars)
{
	int h;

	h = 0;
	while (h <= vars->size_win_h / 2)
		my_mlx_pixel_put(&vars->img, num_rey - 1, h++, vars->color_roof);
	while (h < vars->size_win_h)
		my_mlx_pixel_put(&vars->img, num_rey - 1, h++, vars->color_floor);
}

static void		ft_render_wall_check(t_vars *vars)
{
	if (vars->no_so != -1 && vars->no_so == 0)
		vars->img_tex_print = vars->img_tex_wall_no;
	else if (vars->no_so != -1 && vars->no_so == 1)
		vars->img_tex_print = vars->img_tex_wall_so;
	else if (vars->we_ea != -1 && vars->we_ea == 0)
		vars->img_tex_print = vars->img_tex_wall_we;
	else if (vars->we_ea != -1 && vars->we_ea == 1)
		vars->img_tex_print = vars->img_tex_wall_ea;
}

void			ft_render_wall(t_vars *vars, double len_r_norm, int num)
{
	double		wall_h;
	int			drawstart;
	int			drawend;
	int			wall_y1;
	float		de_ds;

	wall_h = vars->size_win_h / len_r_norm;
	drawstart = (int)(-wall_h / 2) + vars->size_win_h / 2;
	drawend = (int)(wall_h / 2) + vars->size_win_h / 2;
	ft_render_wall_check(vars);
	wall_y1 = drawstart;
	de_ds = (float)drawend - (float)drawstart;
	while (wall_y1 < drawend)
	{
		if (wall_y1 >= 0 && wall_y1 < vars->size_win_h)
			my_mlx_pixel_put(&vars->img, num - 1, wall_y1,
			my_mlx_pixel_take(vars->img_tex_print,
			(int)((vars->x_tex - (int)vars->x_tex) * vars->img_tex_print.w),
			(int)(((float)(wall_y1 - drawstart) / (de_ds)
			* (float)vars->img_tex_print.h))));
		wall_y1++;
	}
}

void			ft_print_wall_sprite(t_vars *vars, double len_r, int num_rey)
{
	double	wall_h;
	int		drst;
	int		drawend;
	int		color;
	int		wall_y1;

	wall_h = vars->size_win_h / len_r;
	drst = (int)(-wall_h / 2) + vars->size_win_h / 2;
	drawend = (int)(wall_h / 2) + vars->size_win_h / 2;
	wall_y1 = drst;
	vars->img_tex_print.h = vars->img_tex_sp.h;
	vars->img_tex_print.w = vars->img_tex_sp.w;
	vars->img_tex_print = vars->img_tex_sp;
	while (wall_y1 < drawend)
	{
		if (wall_y1 >= 0 && wall_y1 < vars->size_win_h)
		{
			color = my_mlx_pixel_take(vars->img_tex_print,
(int)(vars->x_tex_sprt * vars->img_tex_print.w), (int)(((float)(wall_y1 - drst)
	/ ((float)drawend - (float)drst)) * (float)vars->img_tex_print.h));
			if (color > 0)
				my_mlx_pixel_put(&vars->img, (num_rey - 1), wall_y1, color);
		}
		wall_y1++;
	}
}

void			ft_render_sprite(t_vars *vars, int num_rey, double min_angle)
{
	int		i;

	i = 0;
	while (vars->sprite[i].create != -1)
		i++;
	while (i)
	{
		i--;
		if (ft_len_sprt(vars, min_angle, &vars->sprite[i]))
			ft_print_wall_sprite(vars, vars->sprite[i].len_to_sprt, num_rey);
	}
}
