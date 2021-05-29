/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:09:58 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/18 15:59:52 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_GET_NEXT_LINE_H
# define GET_NEXT_LINE_GET_NEXT_LINE_H
# include "unistd.h"
# include "stdlib.h"
# include "libft.h"
# define BUFFER_SIZE 1

size_t				ft_strlen_gn(const char *s);
char				*ft_strchr_gn(const char *string, int symbol);
char				*ft_strjoin_gn(char const *s1, char const *s2);
int					get_next_line(int fd, char **line);
char				*ft_strdup_gn(const char *s);
size_t				ft_strlcpy_gn(char *dst, const char *src);

#endif
