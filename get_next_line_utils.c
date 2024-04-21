/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:18:11 by atorma            #+#    #+#             */
/*   Updated: 2024/04/21 14:26:48 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t	ft_strlen(char *str)
{
	char	*s;

	s = str;
	while (*s)
		s++;
	return (s - str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count && SIZE_MAX / count < size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	memset(p, 0, count * size);
	return (p);
}
