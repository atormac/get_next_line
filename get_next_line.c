/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:42:02 by atorma            #+#    #+#             */
/*   Updated: 2024/04/21 15:23:22 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 8

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

char	*line_create(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_calloc(1, s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	free(s1);
	return (str);
}

char	*read_line(int fd, char *line)
{
	ssize_t	size_read;
	char	buf[BUFFER_SIZE + 1];

	if (line == NULL)
	{
		line = ft_calloc(1, BUFFER_SIZE + 1);
		if (!line)
			return (NULL);
	}
	while (1)
	{
		memset(buf, 0, BUFFER_SIZE + 1);
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(line);
			return (NULL);
		}
		if (size_read == 0)
			return (line);
		line = line_create(line, buf);
		if (!pos_newline(line))
			continue;
		break;
	}
	return (line);
}

char	*parse_line(char *buffer, char **buffer_ptr)
{
	char	*line;
	size_t	line_length;
	size_t	buf_len;

	if (!buffer)
		return (NULL);
	buf_len = ft_strlen(buffer);
	if (buf_len <= 0)
	{
		free(buffer);
		*buffer_ptr = NULL;
		return (NULL);
	}
	line_length = pos_newline(buffer) - buffer;
	if (pos_newline(buffer) == NULL)
		line_length = buf_len;
	line = ft_calloc(1, line_length + 2);
	if (!line)
		return (NULL);
	strncpy(line, buffer, line_length + 1);

	return (line);
}

char	*fix_ptr(char *buffer)
{
	char	*fixed_buf;
	size_t	line_length;
	size_t	buf_len;

	if (!buffer)
		return (NULL);
	line_length = (pos_newline(buffer) - buffer) + 1;
	buf_len = ft_strlen(buffer);
	if (line_length <= buf_len)
	{
		fixed_buf = ft_calloc(1, buf_len - line_length + 1);
		if (!fixed_buf)
			return (NULL);
		strcpy(fixed_buf, buffer + line_length);
		free(buffer);
		return (fixed_buf);
	}
	*buffer = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char *buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buf = read_line(fd, buf);
	line = parse_line(buf, &buf);
	buf = fix_ptr(buf);
	return (line);
}

int main(int argc, char **argv)
{
	int	i = 0;
	int	fd = -1;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else if (argc == 1)
		fd = STDIN_FILENO;
	if (fd < 0)
		return (0);
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("line[%d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
