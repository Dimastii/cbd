/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:05:05 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/17 15:43:55 by cveeta           ###   ########.fr       */
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

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((*ptr1 || *ptr2) && i < n)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		i++;
		ptr1++;
		ptr2++;
	}
	return (0);
}

int			ft_atoi_cb(char **str)
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
		if (dig > 2147483647)
			dig = 2147483647;
	}
	return (dig);
}
