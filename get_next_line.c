/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pameyer <pameyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:18:14 by pameyer           #+#    #+#             */
/*   Updated: 2023/11/14 05:28:00 by pameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static int	read_and_handle(int fd, char *buffer, int *buffer1, char **line)
{
	if (buffer1[0] >= buffer1[1])
	{
		buffer1[1] = read(fd, buffer, BUFFER_SIZE);
		buffer1[0] = 0;
		if (buffer1[1] == -1)
		{
			clear_buffer(buffer);
			if (*line)
				free(*line);
			return (-1);
		}
		else if (buffer1[1] <= 0)
		{
			if (*line && (*line)[0] != '\0')
				return (0);
			if (*line)
				free(*line);
			return (-1);
		}
	}
	return (1);
}

char	*handle_result(int result, char **line)
{
	if (result == 0)
		return (*line);
	else
		return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer1[2] = {0, 0};
	char		*line;
	int			line_length;
	int			result;

	line = NULL;
	line_length = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		result = read_and_handle(fd, buffer, buffer1, &line);
		if (result != 1)
			return (handle_result(result, &line));
		if (buffer[buffer1[0]] == '\n')
		{
			line = append_char(line, '\n', &line_length);
			buffer1[0]++;
			return (line);
		}
		line = append_char(line, buffer[buffer1[0]], &line_length);
		buffer1[0]++;
	}
}
