/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:09:54 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/18 15:55:37 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strchr_gn(const char *string, int symbol)
{
	char *str;
	char sb;

	sb = (char)symbol;
	str = (char*)string;
	while (*str)
	{
		if (*str == sb)
			return (str);
		str++;
	}
	return ((*str == sb) ? str : NULL);
}

size_t			ft_strlen_gn(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char			*ft_strjoin_gn(char const *s1, char const *s2)
{
	char	*str;
	char	*strr;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(len + 1)))
		return (NULL);
	strr = str;
	while (*s1)
		*strr++ = *s1++;
	while (*s2)
		*strr++ = *s2++;
	*strr = '\0';
	return (str);
}

char			*ft_strdup_gn(const char *s)
{
	char	*str;
	char	*strret;

	if (!(str = malloc(ft_strlen(s) + 1)))
		return (NULL);
	strret = str;
	while (*s)
		*str++ = *s++;
	*str = '\0';
	return (strret);
}

size_t			ft_strlcpy_gn(char *dst, const char *src)
{
	size_t		len;
	const char	*sr;

	if (!dst && !src)
		return (0);
	sr = src;
	len = ft_strlen(src);
	while (*sr)
	{
		*(dst++) = *(sr++);
	}
	*dst = '\0';
	return (len);
}
