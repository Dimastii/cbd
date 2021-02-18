/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:28:36 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/15 22:28:36 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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