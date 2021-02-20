/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:58:40 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/15 22:28:31 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			ft_round_sprt_x(double angl, double *x, double *y)
{
	if (cos(angl) < 0)
	{
		*y = ceil(*y) - 0.5;
		*x -= 0.5;
	}
	else if (cos(angl) > 0)
	{
		*y = ceil(*y) - 0.5;
		*x += 0.5;
	}
}

void			ft_round_sprt_y(double angl, double *x, double *y)
{
	if (sin(angl) < 0)
	{
		*x = ceil(*x) - 0.5;
		*y += 0.5;
	}
	else if (sin(angl) > 0)
	{
		*x = ceil(*x) - 0.5;
		*y -= 0.5;
	}
}

void			ft_sort_sprt(t_vars *vars)
{
	t_sprite	temp;
	int			i;
	int			j;

	i = 0;
	while (vars->sprite[i].create != -1)
	{
		j = i + 1;
		while (vars->sprite[j].create != -1)
		{
			if (vars->sprite[j].len_to_sprt < vars->sprite[i].len_to_sprt)
			{
				temp = vars->sprite[j];
				vars->sprite[j] = vars->sprite[i];
				vars->sprite[i] = temp;
			}
			j++;
		}
		i++;
	}
}

static void		ft_angle_sprt(t_vars vars, t_sprite sprt,
							double h_x, double *an_sptr)
{
	if (sprt.enter_on_len_x - vars.x >= 0
	&& sprt.enter_on_len_y - vars.y >= 0)
		*an_sptr = -atan((sprt.enter_on_len_y - vars.y) / (h_x));
	else if (sprt.enter_on_len_x - vars.x >= 0
	&& sprt.enter_on_len_y - vars.y <= 0)
		*an_sptr = -atan((sprt.enter_on_len_y - vars.y) / (h_x));
	else if (sprt.enter_on_len_x - vars.x <= 0
	&& sprt.enter_on_len_y - vars.y <= 0)
		*an_sptr = -atan((sprt.enter_on_len_y - vars.y) / (h_x)) + M_PI;
	else if (sprt.enter_on_len_x - vars.x <= 0
	&& sprt.enter_on_len_y - vars.y >= 0)
		*an_sptr = -atan((sprt.enter_on_len_y - vars.y) / (h_x)) - M_PI;
}

int				ft_len_sprt(t_vars *vars, double ang, t_sprite *sprt)
{
	double		a1;
	double		a2;
	double		angle_sptr;
	double		ang_range;

	ang_range = atan(0.5 / sprt->len_to_sprt);
	ft_round_angle(&ang);
	ft_angle_sprt(*vars, *sprt, sprt->enter_on_len_x - vars->x, &angle_sptr);
	a1 = angle_sptr - ang_range;
	a2 = angle_sptr + ang_range;
	if ((ang >= a1 && ang <= a2))
	{
		vars->x_tex_sprt = (ang - a1) / (a2 - a1);
		return (1);
	}
	if ((a2 >= M_PI || a1 <= -M_PI)
	&& (sin(ang) >= sin(a2) && sin(ang) <= sin(a1)))
	{
		if (a2 >= M_PI && ang < 0)
			vars->x_tex_sprt = ((ang + 2 * M_PI) - a1) / (a2 - a1);
		else if (a1 <= -M_PI && ang > 0)
			vars->x_tex_sprt = ((ang - 2 * M_PI) - a1) / (a2 - a1);
		return (1);
	}
	return (0);
}
