/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:41 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:30:43 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	put_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != ' ')
				mlx_put_image_to_window(data->mlx, data->window, data->back,
					j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

static void	put_tile(t_data *data, int i, int j)
{
	if (data->map[i][j] == '1')
		mlx_put_image_to_window(data->mlx, data->window, data->wall,
			j * TILE_SIZE, i * TILE_SIZE);
	else if (is_player(data->map[i][j]))
	{
		mlx_put_image_to_window(data->mlx, data->window, data->player,
			j * TILE_SIZE, i * TILE_SIZE);
		data->player_x = j;
		data->player_y = i;
	}
}

void	create_map(t_data *data)
{
	int	i;
	int	j;

	/*
	** Temporary 2D debug renderer kept from the first parser step.
	** The active cub3D view now uses render_frame() in raycast.c.
	*/
	put_floor(data);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			put_tile(data, i, j);
			j++;
		}
		i++;
	}
}
