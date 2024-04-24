/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:18:02 by atorma            #+#    #+#             */
/*   Updated: 2024/04/24 19:18:12 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	register unsigned char	*p1;
	register unsigned char	*p2;

	if (!dst && !src)
		return (0);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	while (n--)
		*p1++ = *p2++;
	return (dst);
}

size_t	ft_strlen(char *str)
{
	char	*s;

	s = str;
	while (*s)
		s++;
	return (s - str);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	n;
	size_t	src_len;

	n = dstsize;
	src_len = ft_strlen(src);
	while (n > 1 && *src)
	{
		*dst++ = *src++;
		n--;
	}
	if (dstsize != 0)
		*dst = 0;
	return (src_len);
}

char	*pos_newline(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}
