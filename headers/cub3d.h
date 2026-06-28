/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:52 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:30:54 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 32
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define MOVE_SPEED 0.15
# define ROT_SPEED 0.08

# define KEY_PRESS 2
# define MOUSE_PRESS 17
# define KEY_ESC 65307

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361

# define A 97
# define S 115
# define D 100
# define W 119

# define MAP_CHARS " 01NSEW"
# define PLAYER_CHARS "NSEW"

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_texture
{
	t_img	img;
	int		width;
	int		height;
}				t_texture;

typedef enum s_errorlst
{
	PARAMETROS,
	MALLOCERROR,
	FD,
	MLX_ERROR,
	IMG_ERROR,
	CUB,
	CONFIG_ERROR,
	COLOR_ERROR,
	NOTRECTANGULAR,
	NOTWALLS,
	INVALID_CHARS,
	INVALID_PE,
	NOTPLAYER,
	MAPERROR
}		t_errorlst;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	void		*back;
	void		*wall;
	void		*player;
	t_texture	textures[4];
	t_img		frame;
	char		*north_tex;
	char		*south_tex;
	char		*west_tex;
	char		*east_tex;
	int			floor_color;
	int			ceiling_color;
	bool		floor_set;
	bool		ceiling_set;
	int			size_x;
	int			size_y;
	int			fd;
	int			player_x;
	int			player_y;
	char		player_dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		**map;
	char		**map_copy;
	int			width;
	int			height;
	int			player_count;
	bool		game_over;
}				t_data;

char	**duplicate_map(char **original, int height, t_data *data);
void	flood_fill_mark(t_data *data, int row, int col);

void	map_checker(t_data *data);

void	handle_error(t_errorlst error, t_data *data);
int		destroy_all(t_data *data);

int		ft_init(t_data *data, char **argv);

int		key_hook(int keycode, t_data *data);

void	load_textures(t_data *data);

void	game_init(t_data *data);
int		game_loop(t_data *data);
void	render_frame(t_data *data);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	create_map(t_data *data);

int		count_lines(int fd);
int		line_length(char *line);
void	free_map(char **map);
void	free_data(t_data *data);

#endif
