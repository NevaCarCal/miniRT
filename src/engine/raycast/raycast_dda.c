/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by brimarti          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast_internal.h"

static char	map_at(t_data *data, int x, int y)
{
	if (y < 0 || x < 0 || y >= data->height)
		return ('1');
	if (x >= line_length(data->map[y]))
		return ('1');
	return (data->map[y][x]);
}

static void	step_x_ray(t_ray *ray)
{
	ray->side_dist_x += ray->delta_dist_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
	if (ray->step_x > 0)
		ray->wall_dir = 'W';
	else
		ray->wall_dir = 'E';
}

static void	step_y_ray(t_ray *ray)
{
	ray->side_dist_y += ray->delta_dist_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
	if (ray->step_y > 0)
		ray->wall_dir = 'N';
	else
		ray->wall_dir = 'S';
}

static void	set_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	run_dda(t_data *data, t_ray *ray)
{
	/*
	** DDA jumps from grid line to grid line. Whichever side distance
	** is smaller tells us which map square the ray enters next.
	*/
	while (map_at(data, ray->map_x, ray->map_y) != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
			step_x_ray(ray);
		else
			step_y_ray(ray);
	}
	set_wall_distance(ray);
	select_wall_texture(data, ray);
}
