/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:28:07 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:28:12 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static int	is_blank(char *line)
{
	line = skip_spaces(line);
	return (*line == '\n' || *line == '\0');
}

static void	check_filename(char *argv, t_data *data)
{
	if (ft_strlen(argv) < 4)
		handle_error(CUB, data);
	argv = argv + (ft_strlen(argv) - 4);
	if (ft_strncmp(argv, ".cub", 4))
		handle_error(CUB, data);
}

static char	*dup_clean(char *line, t_data *data)
{
	int		i;
	int		end;
	char	*copy;

	line = skip_spaces(line);
	end = line_length(line);
	while (end > 0 && (line[end - 1] == ' ' || line[end - 1] == '\t'))
		end--;
	copy = malloc(sizeof(char) * (end + 1));
	if (!copy)
		handle_error(MALLOCERROR, data);
	i = 0;
	while (i < end)
	{
		copy[i] = line[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	read_lines(char *path, char ***lines, int *total, t_data *data)
{
	int	fd;
	int	i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error(FD, data);
	*total = count_lines(fd);
	close(fd);
	*lines = malloc(sizeof(char *) * (*total + 1));
	if (!*lines)
		handle_error(MALLOCERROR, data);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error(FD, data);
	i = 0;
	while (i < *total)
		(*lines)[i++] = get_next_line(fd);
	(*lines)[i] = NULL;
	close(fd);
}

static void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

static void	set_texture(char **target, char *line, t_data *data)
{
	if (*target)
		handle_error(CONFIG_ERROR, data);
	*target = dup_clean(line, data);
}

static int	parse_number(char **line, t_data *data)
{
	int	value;

	value = 0;
	*line = skip_spaces(*line);
	if (**line < '0' || **line > '9')
		handle_error(COLOR_ERROR, data);
	while (**line >= '0' && **line <= '9')
	{
		value = value * 10 + (**line - '0');
		if (value > 255)
			handle_error(COLOR_ERROR, data);
		(*line)++;
	}
	*line = skip_spaces(*line);
	return (value);
}

static int	parse_rgb(char *line, t_data *data)
{
	int	r;
	int	g;
	int	b;

	r = parse_number(&line, data);
	if (*line++ != ',')
		handle_error(COLOR_ERROR, data);
	g = parse_number(&line, data);
	if (*line++ != ',')
		handle_error(COLOR_ERROR, data);
	b = parse_number(&line, data);
	line = skip_spaces(line);
	if (*line != '\0' && *line != '\n')
		handle_error(COLOR_ERROR, data);
	return ((r << 16) | (g << 8) | b);
}

static int	parse_texture(t_data *data, char *p)
{
	if (ft_strncmp(p, "NO", 2) == 0 && (p[2] == ' ' || p[2] == '\t'))
		set_texture(&data->north_tex, p + 2, data);
	else if (ft_strncmp(p, "SO", 2) == 0 && (p[2] == ' ' || p[2] == '\t'))
		set_texture(&data->south_tex, p + 2, data);
	else if (ft_strncmp(p, "WE", 2) == 0 && (p[2] == ' ' || p[2] == '\t'))
		set_texture(&data->west_tex, p + 2, data);
	else if (ft_strncmp(p, "EA", 2) == 0 && (p[2] == ' ' || p[2] == '\t'))
		set_texture(&data->east_tex, p + 2, data);
	else
		return (0);
	return (1);
}

static int	parse_floor_color(t_data *data, char *p)
{
	if (*p != 'F' || (p[1] != ' ' && p[1] != '\t') || data->floor_set)
		return (0);
	data->floor_color = parse_rgb(p + 1, data);
	data->floor_set = true;
	return (1);
}

static int	parse_ceiling_color(t_data *data, char *p)
{
	if (*p != 'C' || (p[1] != ' ' && p[1] != '\t') || data->ceiling_set)
		return (0);
	data->ceiling_color = parse_rgb(p + 1, data);
	data->ceiling_set = true;
	return (1);
}

static int	parse_config_line(t_data *data, char *line)
{
	char	*p;

	p = skip_spaces(line);
	if (parse_texture(data, p))
		return (1);
	if (parse_floor_color(data, p))
		return (1);
	if (parse_ceiling_color(data, p))
		return (1);
	return (0);
}

static void	set_camera_north(t_data *data)
{
	data->dir_x = 0;
	data->dir_y = -1;
	data->plane_x = 0.66;
	data->plane_y = 0;
}

static void	set_camera_south(t_data *data)
{
	data->dir_x = 0;
	data->dir_y = 1;
	data->plane_x = -0.66;
	data->plane_y = 0;
}

static void	set_camera_east(t_data *data)
{
	data->dir_x = 1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
}

static void	set_camera_west(t_data *data)
{
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = -0.66;
}

static int	is_map_start(char *line)
{
	line = skip_spaces(line);
	return (*line == '1' || *line == '0' || *line == 'N'
		|| *line == 'S' || *line == 'E' || *line == 'W');
}

static char	*dup_map_line(char *line, t_data *data)
{
	int		i;
	int		len;
	char	*copy;

	len = line_length(line);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		handle_error(MALLOCERROR, data);
	i = 0;
	while (i < len)
	{
		copy[i] = line[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	copy_map(t_data *data, char **lines, int start, int total)
{
	int	i;
	int	len;

	data->height = total - start;
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		handle_error(MALLOCERROR, data);
	i = 0;
	while (i < data->height)
	{
		data->map[i] = dup_map_line(lines[start + i], data);
		len = line_length(data->map[i]);
		if (len > data->width)
			data->width = len;
		i++;
	}
	data->map[i] = NULL;
	data->size_x = data->width;
	data->size_y = data->height;
}

static void	parse_file(t_data *data, char **lines, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (is_blank(lines[i]))
			i++;
		else if (parse_config_line(data, lines[i]))
			i++;
		else if (is_map_start(lines[i]))
			break ;
		else
			handle_error(CONFIG_ERROR, data);
	}
	if (i == total || !data->north_tex || !data->south_tex
		|| !data->west_tex || !data->east_tex
		|| !data->floor_set || !data->ceiling_set)
		handle_error(CONFIG_ERROR, data);
	copy_map(data, lines, i, total);
}

static void	set_camera(t_data *data)
{
	data->pos_x = data->player_x + 0.5;
	data->pos_y = data->player_y + 0.5;
	if (data->player_dir == 'N')
		set_camera_north(data);
	else if (data->player_dir == 'S')
		set_camera_south(data);
	else if (data->player_dir == 'E')
		set_camera_east(data);
	else if (data->player_dir == 'W')
		set_camera_west(data);
}

int	ft_init(t_data *data, char **argv)
{
	char	**lines;
	int		total;

	lines = NULL;
	check_filename(argv[1], data);
	read_lines(argv[1], &lines, &total, data);
	parse_file(data, lines, total);
	free_lines(lines);
	map_checker(data);
	set_camera(data);
	return (0);
}
