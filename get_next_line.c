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
	char	tmp_buf[BUFFER_SIZE + 1];

	while (1)
	{
		size_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(line);
			return (NULL);
		}
		else if (size_read == 0)
			return (line);
		tmp_buf[size_read] = 0;
		line = line_create(line, tmp_buf);
		if (!line)
			return (NULL);
		if (pos_newline(tmp_buf))
			break ;
	}
	return (line);
}

char	*dup_line(char *buffer, size_t buf_len)
{
	char	*line;
	char	*line_break;
	size_t	line_length;

	if (buf_len <= 0)
		return (NULL);
	line_break = pos_newline(buffer);
	line_length = line_break - buffer;
	if (line_break == NULL)
		line_length = buf_len - 1;
	line = ft_calloc(1, line_length + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, line_length + 2);
	return (line);
}

void	move_remaining(char *buffer, size_t buf_len)
{
	size_t	line_length;
	char	*line_break;

	if (!buffer)
		return ;
	line_break = pos_newline(buffer);
	line_length = buf_len;
	if (line_break)
		line_length = (line_break - buffer) + 1;
	ft_strlcpy(buffer, buffer + line_length, buf_len - line_length + 1);
	return ;
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
	line = dup_line(buf, buf_len);
	if (!line)
	{
		free(buf);
		buf = NULL;
	}
	move_remaining(buf, buf_len);
	return (line);
}
