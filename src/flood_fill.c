/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by brimarti          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This file is intentionally not part of the mandatory cub3D validation.
**
** In so_long, flood fill answers a mandatory question:
** "Can the player reach all objectives and the exit?"
**
** In cub3D, the mandatory parser answers a different question:
** "Is the map closed so the raycaster can never look outside it?"
**
** We keep this helper for a future videogame layer. For example, when you add
** coins, doors, enemies, or an exit, you can copy the parsed map and use this
** flood fill to mark every tile reachable from the player's starting position.
*/

static int	is_fill_wall(char c)
{
	return (c == '1' || c == ' ' || c == '\0');
}

static int	is_inside_map(t_data *data, int row, int col)
{
	if (row < 0 || col < 0 || row >= data->height)
		return (0);
	if (col >= line_length(data->map_copy[row]))
		return (0);
	return (1);
}

void	flood_fill_mark(t_data *data, int row, int col)
{
	char	current;

	if (!data->map_copy || !is_inside_map(data, row, col))
		return ;
	current = data->map_copy[row][col];
	if (current == 'r' || is_fill_wall(current))
		return ;
	data->map_copy[row][col] = 'r';
	flood_fill_mark(data, row + 1, col);
	flood_fill_mark(data, row - 1, col);
	flood_fill_mark(data, row, col + 1);
	flood_fill_mark(data, row, col - 1);
}
