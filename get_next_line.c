/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:42:02 by atorma            #+#    #+#             */
/*   Updated: 2024/04/22 16:01:01 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 8

char	*pos_newline(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(char *str);
void	*ft_calloc(size_t count, size_t size);

char	*line_create(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_calloc(1, s1_len + s2_len + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, s2_len + 1);
	free(s1);
	return (str);
}

char	*read_line(int fd, char *line)
{
	ssize_t	size_read;
	char	buf[BUFFER_SIZE + 1];

	while (1)
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(line);
			return (NULL);
		}
		if (size_read == 0)
			return (line);
		buf[size_read] = 0;
		line = line_create(line, buf);
		if (!line)
			return (NULL);
		if (pos_newline(buf))
			break ;
	}
	return (line);
}

char	*parse_line(char *buffer, size_t buf_len)
{
	char	*line;
	char	*line_break;
	size_t	line_length;

	if (buf_len <= 0)
		return (NULL);
	line_break = pos_newline(buffer);
	line_length = line_break - buffer;
	if (line_break == NULL)
	{
		line_length = buf_len;
		line_length--;
	}
	line = ft_calloc(1, line_length + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, line_length + 2);
	return (line);
}

char	*trim_buffer(char *buffer, size_t buf_len)
{
	char	*fixed_buf;
	size_t	line_length;

	if (!buffer)
		return (NULL);
	line_length = (pos_newline(buffer) - buffer) + 1;
	if (line_length <= buf_len)
	{
		fixed_buf = ft_calloc(1, buf_len - line_length + 1);
		if (!fixed_buf)
			return (NULL);
		ft_strlcpy(fixed_buf, buffer + line_length, buf_len - line_length + 1);
		free(buffer);
		return (fixed_buf);
	}
	*buffer = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	size_t		buf_len;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf == NULL)
	{
		buf = ft_calloc(1, BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
	}
	buf = read_line(fd, buf);
	if (!buf)
		return (NULL);
	buf_len = ft_strlen(buf);
	line = parse_line(buf, buf_len);
	buf = trim_buffer(buf, buf_len);
	if (!buf || !line)
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}
