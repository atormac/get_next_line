#include <stdlib.h>
#include <unistd.h>
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
	int	s1_len = strlen(s1);
	int s2_len = strlen(s2);

	str = calloc(1, s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	free(s1);
	return (str);
}

char	*read_line(int fd, char *line)
{
	size_t	size_read;
	char	buf[BUFFER_SIZE + 1];

	buf[BUFFER_SIZE] = 0;
	if (line == NULL)
	{
		line = calloc(1, BUFFER_SIZE + 1);
		if (!line)
			return (NULL);
	}
	while (1)
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read <= 0)
		{
			free(line);
			return (NULL);
		}
		line = line_create(line, buf);
		if (!pos_newline(buf))
			continue;
		break;
	}
	return (line);
}

char	*parse_line(char *buffer)
{
	char	*line;
	size_t	line_length;

	if (!buffer)
		return (NULL);
	line_length = pos_newline(buffer) - buffer;
	line = calloc(1, line_length + 1);
	if (!line)
		return (NULL);
	strncpy(line, buffer, line_length);

	return (line);
}

char	*fix_ptr(char *buffer)
{
	char	*fixed_buf;
	size_t	line_length;

	if (!buffer)
		return (NULL);
	line_length = pos_newline(buffer) - buffer;
	line_length++;
	if (line_length <= BUFFER_SIZE)
	{
		fixed_buf = calloc(1, BUFFER_SIZE - line_length + 1);
		if (!fixed_buf)
			return (NULL);
		strcpy(fixed_buf, buffer + line_length);
		free(buffer);
		return (fixed_buf);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char *buf;
	char		*line;

	buf = read_line(fd, buf);
	line = parse_line(buf);
	buf = fix_ptr(buf);
	return (line);
}

int main(int argc, char **argv)
{
	int	i = 0;
	if (argc != 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	while (i < 4)
	{
		char *line = get_next_line(fd);
		printf("line[%d]: %s\n", i, line);
		i++;
	}
	close(fd);
	return (0);
}
