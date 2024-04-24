/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:42:02 by atorma            #+#    #+#             */
/*   Updated: 2024/04/23 20:14:38 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*pos_newline(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(char *str);

static char	*line_create(char *s1, char *s2, size_t s2_len)
{
	char	*str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	str = malloc(s1_len + s2_len + 1);
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

static char	*read_line(int fd, char *buf)
{
	char	tmp_buf[BUFFER_SIZE + 1];
	ssize_t	size_read;

	while (1)
	{
		size_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (size_read <= 0)
			break ;
		tmp_buf[size_read] = 0;
		buf = line_create(buf, tmp_buf, size_read);
		if (!buf || pos_newline(tmp_buf))
			break ;
	}
	return (buf);
}

static char	*dup_line(char *buffer)
{
	char	*line;
	char	*line_break;
	size_t	line_length;
	size_t	buf_len;

	if (!buffer)
		return (NULL);
	buf_len = ft_strlen(buffer);
	if (buf_len == 0)
		return (NULL);
	line_break = pos_newline(buffer);
	line_length = line_break - buffer;
	if (!line_break)
		line_length = buf_len - 1;
	line = malloc(line_length + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, line_length + 2);
	ft_strlcpy(buffer, buffer + line_length + 1, buf_len - line_length + 2);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf == NULL)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		buf[0] = 0;
	}
	buf = read_line(fd, buf);
	line = dup_line(buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}
