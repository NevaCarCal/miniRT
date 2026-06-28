#ifndef RAYCAST_INTERNAL_H
# define RAYCAST_INTERNAL_H

# include "cub3d.h"

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
	t_texture	*texture;
} 		t_ray;

void	select_wall_texture(t_data *data, t_ray *ray);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
void	get_wall_hit_x(t_data *data, t_ray *ray, double *wall_x);
void	init_ray(t_data *data, t_ray *ray, int x);
void	set_step(t_data *data, t_ray *ray);
void	run_dda(t_data *data, t_ray *ray);
void	draw_column(t_data *data, int x, t_ray *ray);

#endif
