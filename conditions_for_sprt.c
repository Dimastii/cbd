/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_for_sprt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:08:14 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 22:11:28 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void				while_cx_if_sprt(t_vars *vars, int *n_sprt)
{
	if (vars->lv.y < MAPW && vars->lv.y > 0 && vars->lv.cx > 0
		&& vars->map[(int)vars->lv.cx - vars->we_ea][(int)vars->lv.y] == '2')
	{
		if (vars->sprite[*n_sprt].len_to_sprt == -1)
		{
			vars->sprite[*n_sprt].enter_on_len_x = vars->lv.cx;
			vars->sprite[*n_sprt].enter_on_len_y = vars->lv.y;
			ft_round_sprt_x(vars->min_angle,
							&vars->sprite[*n_sprt].enter_on_len_x,
							&vars->sprite[*n_sprt].enter_on_len_y);
			vars->sprite[*n_sprt].len_to_sprt = sqrt(
					pow(vars->sprite[*n_sprt].enter_on_len_x - vars->x, 2) +
					pow(vars->sprite[*n_sprt].enter_on_len_y - vars->y, 2));
			vars->sprite[*n_sprt].create = 1;
			(*n_sprt)++;
		}
	}
}

void				while_cy_if_sprt(t_vars *vars, int *n_sprt)
{
	if (vars->lv.x < MAPH && vars->lv.x > 0
		&& vars->map[(int)vars->lv.x][(int)vars->lv.cy - vars->no_so] == '2')
	{
		if (vars->sprite[*n_sprt].len_to_sprt == -1)
		{
			vars->sprite[*n_sprt].enter_on_len_x = vars->lv.x;
			vars->sprite[*n_sprt].enter_on_len_y = vars->lv.cy;
			ft_round_sprt_y(vars->min_angle,
							&vars->sprite[*n_sprt].enter_on_len_x,
							&vars->sprite[*n_sprt].enter_on_len_y);
			vars->sprite[*n_sprt].len_to_sprt = sqrt(
					pow(vars->sprite[*n_sprt].enter_on_len_x - vars->x, 2) +
					pow(vars->sprite[*n_sprt].enter_on_len_y - vars->y, 2));
			vars->sprite[*n_sprt].create = 1;
			(*n_sprt)++;
		}
	}
}
