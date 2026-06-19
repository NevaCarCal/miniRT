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

#include "cub3d.h"

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	char	wall_dir;
}				t_ray;

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static char	map_at(t_data *data, int x, int y)
{
	if (y < 0 || x < 0 || y >= data->height)
		return ('1');
	if (x >= line_length(data->map[y]))
		return ('1');
	return (data->map[y][x]);
}

static void	init_ray(t_data *data, t_ray *ray, int x)
{
	/*
	** camera_x converts a screen column into a value from -1 to 1.
	** -1 is the left side of the camera plane, 0 is the center, 1 is right.
	*/
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	set_x_step(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x)
			* ray->delta_dist_x;
	}
}

static void	set_y_step(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y)
			* ray->delta_dist_y;
	}
}

static void	set_step(t_data *data, t_ray *ray)
{
	/*
	** step_x/step_y say whether the ray walks left/right and up/down.
	** side_dist_* is the distance from the player to the first grid border.
	*/
	set_x_step(data, ray);
	set_y_step(data, ray);
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

static void	run_dda(t_data *data, t_ray *ray)
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
}

static int	wall_color(t_ray *ray)
{
	if (ray->wall_dir == 'N')
		return (0xC8C8C8);
	if (ray->wall_dir == 'S')
		return (0xA8A8A8);
	if (ray->wall_dir == 'E')
		return (0x808080);
	return (0x606060);
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

static void	draw_column(t_data *data, int x, t_ray *ray)
{
	int	draw_start;
	int	draw_end;
	int	y;

	wall_limits(ray, &draw_start, &draw_end);
	y = 0;
	while (y < draw_start)
		put_pixel(&data->frame, x, y++, data->ceiling_color);
	while (y <= draw_end)
		put_pixel(&data->frame, x, y++, wall_color(ray));
	while (y < WIN_HEIGHT)
		put_pixel(&data->frame, x, y++, data->floor_color);
}

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
