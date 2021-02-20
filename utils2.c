/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:03:04 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 20:03:04 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

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
