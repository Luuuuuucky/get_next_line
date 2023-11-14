/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pameyer <pameyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:18:11 by pameyer           #+#    #+#             */
/*   Updated: 2023/11/14 08:29:38 by pameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_buffer(char *buffer)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		buffer[i] = '\0';
}

char	*append_char(char *line, char c, int *line_length)
{
	int		i;
	char	*new_line;

	i = -1;
	new_line = (char *)malloc(*line_length + 2);
	if (new_line == NULL)
	{
		free(line);
		return (NULL);
	}
	if (line)
	{
		while (++i < *line_length)
			new_line[i] = line[i];
		free(line);
	}
	new_line[*line_length] = c;
	new_line[*line_length + 1] = '\0';
	(*line_length)++;
	return (new_line);
}
