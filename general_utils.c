/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:28:36 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 22:23:21 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	*(unsigned int*)(data->addr +
	(y * data->line_length + x * (data->bits_per_pixel / 8))) = color;
}

int				my_mlx_pixel_take(t_image data, int x, int y)
{
	return (*(int*)(data.addr +
	(y * data.line_length + x * (data.bits_per_pixel / 8))));
}

void			ft_round_angle(double *ang)
{
	if (*ang < 0)
		while (*ang < -(2.0 * M_PI))
			*ang += (2.0 * M_PI);
	else if (*ang > 0)
		while (*ang > (2.0 * M_PI))
			*ang -= (2.0 * M_PI);
	if (*ang > M_PI)
		*ang -= (2.0 * M_PI);
	if (*ang < -M_PI)
		*ang += (2.0 * M_PI);
}

void			ft_round(double *cx, double *cy, t_vars *vars)
{
	if (vars->cos_ang > 0 && vars->sin_ang > 0)
	{
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
	}
	else if (vars->cos_ang < 0 && vars->sin_ang > 0)
	{
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx - 1;
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
	}
	else if (vars->cos_ang < 0 && vars->sin_ang < 0)
	{
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx - 1;
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) : *cy + 1;
	}
	else if (vars->cos_ang > 0 && vars->sin_ang < 0)
	{
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) : *cy + 1;
	}
}
