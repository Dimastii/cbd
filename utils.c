/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:05:05 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/16 15:30:08 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		   || c == '\r')
		return (1);
	return (0);
}

int			ft_atoi(char **str)
{
	int				dig;

	dig = 0;
	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '\n' || *(*str) == '\v' || *(*str) == '\f'
		   || *(*str) == '\r')
		(*str)++;
	if (*(*str) == '-')
	{
		(*str)++;
		return (0);
	}
	while (ft_isdigit(*(*str)))
	{
		dig = dig * 10 + *(*str) - '0';
		(*str)++;
		if (dig > 3000)
			dig = 3000;
	}
	return (dig);
}
