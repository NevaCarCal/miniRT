/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by brimarti          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast_internal.h"

void	render_frame(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		set_step(data, &ray);
		run_dda(data, &ray);
		draw_column(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->frame.img, 0, 0);
}
