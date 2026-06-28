/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by brimarti          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast_internal.h"

void	select_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->wall_dir == 'N')
		ray->texture = &data->textures[0];
	else if (ray->wall_dir == 'S')
		ray->texture = &data->textures[1];
	else if (ray->wall_dir == 'W')
		ray->texture = &data->textures[2];
	else
		ray->texture = &data->textures[3];
}

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	dst = texture->img.addr + (y * texture->img.line_length
			+ x * (texture->img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	get_wall_hit_x(t_data *data, t_ray *ray, double *wall_x)
{
	if (ray->side == 0)
		*wall_x = data->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		*wall_x = data->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	*wall_x -= floor(*wall_x);
}