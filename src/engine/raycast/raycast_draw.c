/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by brimarti          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast_internal.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	wall_limits(t_ray *ray, int *start, int *end)
{
	int	line_height;

	/*
	** We use perpendicular distance, not raw ray distance. That avoids the
	** classic fish-eye distortion where side walls look curved.
	*/
	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	*start = -line_height / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = line_height / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

static void	draw_textured_wall(t_data *data, int x, t_ray *ray,
	int draw_start, int draw_end)
{
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		line_height;

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	get_wall_hit_x(data, ray, &wall_x);
	tex_x = (int)(wall_x * ray->texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = ray->texture->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = ray->texture->width - tex_x - 1;
	tex_step = (double)ray->texture->height / line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * tex_step;
	while (draw_start <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ray->texture->height)
			tex_y = ray->texture->height - 1;
		put_pixel(&data->frame, x, draw_start,
			get_texture_color(ray->texture, tex_x, tex_y));
		tex_pos += tex_step;
		draw_start++;
	}
}

void	draw_column(t_data *data, int x, t_ray *ray)
{
	int	draw_start;
	int	draw_end;
	int	y;

	wall_limits(ray, &draw_start, &draw_end);
	y = 0;
	while (y < draw_start)
		put_pixel(&data->frame, x, y++, data->ceiling_color);
	draw_textured_wall(data, x, ray, draw_start, draw_end);
	y = draw_end + 1;
	while (y < WIN_HEIGHT)
		put_pixel(&data->frame, x, y++, data->floor_color);
}
