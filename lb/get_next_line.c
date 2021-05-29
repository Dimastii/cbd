/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:01:51 by cveeta            #+#    #+#             */
/*   Updated: 2020/12/07 14:15:58 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include "stdio.h"

int				ft_free(char **s1)
{
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	return (0);
}

int				ft_check(char **stat, char **line)
{
	char *pos_n;

	if (*stat)
	{
		if ((pos_n = ft_strchr_gn(*stat, '\n')))
		{
			*pos_n++ = '\0';
			if (!(*line = ft_strdup_gn(*stat)))
			{
				ft_free(&(*stat));
				return (-1);
			}
			ft_strlcpy_gn(*stat, pos_n);
			return (0);
		}
		else
		{
			*line = ft_strdup_gn(*stat);
			ft_free(&(*stat));
		}
	}
	else
		*line = ft_strdup_gn("");
	return (1);
}

int				ft_reed(char **stat, char **line, int fd, char *bf)
{
	int		r_b;
	char	*pos_n;
	char	*fre;

	pos_n = NULL;
	while (!pos_n && (r_b = read(fd, bf, BUFFER_SIZE)))
	{
		bf[r_b] = '\0';
		if ((pos_n = ft_strchr_gn(bf, '\n')))
		{
			*pos_n++ = '\0';
			fre = *stat;
			*stat = ft_strdup_gn(pos_n);
			ft_free(&fre);
		}
		fre = *line;
		*line = ft_strjoin_gn(*line, bf);
		ft_free(&fre);
	}
	ft_free(&bf);
	if (r_b == 0)
		return (ft_free(&(*stat)));
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char			*bf;
	static char		*stat[1024];

	bf = NULL;
	if (fd < 0 || !line || BUFFER_SIZE < 1
	|| !(bf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)))
	|| (read(fd, 0, 0)) < 0)
	{
		if (bf)
			free(bf);
		return (-1);
	}
	*line = NULL;
	if (ft_check(&stat[fd], line))
		return (ft_reed(&stat[fd], line, fd, bf));
	free(bf);
	return (1);
}
