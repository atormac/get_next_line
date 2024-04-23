/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:25:51 by atorma            #+#    #+#             */
/*   Updated: 2024/04/22 16:26:37 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

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
	while (i < 5)
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
