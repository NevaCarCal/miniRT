/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:31:16 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:31:19 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (lines);
}

int	line_length(char *line)
{
	int		length;

	length = 0;
	while (line[length] && line[length] != '\n')
		length++;
	return (length);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->map)
			free_map(data->map);
		if (data->map_copy)
			free_map(data->map_copy);
		free(data->north_tex);
		free(data->south_tex);
		free(data->west_tex);
		free(data->east_tex);
	}
}
