/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:18:11 by atorma            #+#    #+#             */
/*   Updated: 2024/04/22 14:52:07 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdint.h>

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

void	*ft_memset(void *b, int c, size_t len)
{
	register unsigned char	*p;

	p = b;
	while (len-- > 0)
		*p++ = c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count && SIZE_MAX / count < size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
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
