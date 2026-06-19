/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:27:38 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:27:41 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || is_player(c));
}

static int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

static char	map_at(t_data *data, int row, int col)
{
	if (row < 0 || col < 0 || row >= data->height)
		return (' ');
	if (col >= line_length(data->map[row]))
		return (' ');
	return (data->map[row][col]);
}

static void	save_player(t_data *data, int i, int j)
{
	data->player_count++;
	data->player_x = j;
	data->player_y = i;
	data->player_dir = data->map[i][j];
}

static void	check_map_cell(t_data *data, int i, int j)
{
	if (!is_valid_char(data->map[i][j]))
		handle_error(INVALID_CHARS, data);
	if (is_player(data->map[i][j]))
		save_player(data, i, j);
}

static void	check_player_and_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			check_map_cell(data, i, j);
			j++;
		}
		i++;
	}
	if (data->player_count != 1)
		handle_error(INVALID_PE, data);
}

static void	check_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_walkable(data->map[i][j])
				&& (map_at(data, i - 1, j) == ' '
					|| map_at(data, i + 1, j) == ' '
					|| map_at(data, i, j - 1) == ' '
					|| map_at(data, i, j + 1) == ' '))
				handle_error(NOTWALLS, data);
			j++;
		}
		i++;
	}
}

void	map_checker(t_data *data)
{
	if (!data->map || !data->map[0])
		handle_error(MAPERROR, data);
	check_player_and_chars(data);
	check_closed(data);
	data->map_copy = duplicate_map(data->map, data->height, data);
	if (!data->map_copy)
		handle_error(MALLOCERROR, data);
}
