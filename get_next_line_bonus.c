/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:17:48 by atorma            #+#    #+#             */
/*   Updated: 2024/05/01 15:58:20 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*pos_newline(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);

static char	*line_join(char *s1, size_t s1_len, char *s2, size_t s2_len)
{
	char	*ret;

	ret = malloc(s1_len + s2_len + 1);
	if (!ret)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(ret, s1, s1_len);
	ft_memcpy(ret + s1_len, s2, s2_len);
	ret[s1_len + s2_len] = 0;
	free(s1);
	return (ret);
}

static char	*read_line(int fd, char *buf, size_t buf_size)
{
	char	tmp_buf[BUFFER_SIZE + 1];
	ssize_t	size_read;

	while (1)
	{
		size_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (size_read == -1)
			buf[0] = 0;
		if (size_read <= 0)
			break ;
		tmp_buf[size_read] = 0;
		buf = line_join(buf, buf_size, tmp_buf, size_read);
		buf_size += size_read;
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

	if (!buffer || *buffer == 0)
		return (NULL);
	buf_len = ft_strlen(buffer);
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
	static char	*buf[256];
	size_t		buf_size;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 256)
		return (NULL);
	if (buf[fd] == NULL)
	{
		buf[fd] = malloc(BUFFER_SIZE + 1);
		if (!buf[fd])
			return (NULL);
		buf[fd][0] = 0;
	}
	buf_size = ft_strlen(buf[fd]);
	if (!pos_newline(buf[fd]))
		buf[fd] = read_line(fd, buf[fd], buf_size);
	line = dup_line(buf[fd]);
	if (buf[fd] && !pos_newline(line))
	{
		free(buf[fd]);
		buf[fd] = NULL;
	}
	return (line);
}
