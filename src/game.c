/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:29:32 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:29:34 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	frame_init(t_data *data)
{
	/*
	** The frame image is our drawing buffer. We paint pixels into memory first
	** and then send the whole image to the window in one MiniLibX call.
	*/
	data->frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->frame.img)
		handle_error(IMG_ERROR, data);
	data->frame.addr = mlx_get_data_addr(data->frame.img,
			&data->frame.bits_per_pixel, &data->frame.line_length,
			&data->frame.endian);
	if (!data->frame.addr)
		handle_error(IMG_ERROR, data);
}

void	game_init(t_data *data)
{
	data->mlx = mlx_init();
	if (NULL == data->mlx)
		handle_error(MLX_ERROR, data);
	data->window = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (NULL == data->window)
		handle_error(MLX_ERROR, data);
	frame_init(data);
	render_frame(data);
	mlx_hook(data->window, KEY_PRESS, 1L >> 0, key_hook, data);
	mlx_hook(data->window, MOUSE_PRESS, 0, destroy_all, data);
	data->game_over = false;
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}

int	game_loop(t_data *data)
{
	if (data->game_over)
	{
		destroy_all(data);
		exit(0);
	}
	return (0);
}
