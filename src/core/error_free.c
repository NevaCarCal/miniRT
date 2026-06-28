/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:27:52 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:27:55 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_errors(t_errorlst error, char *error_msg[])
{
	write(2, "ERROR: ", 7);
	if (error == FD)
		perror("open");
	else if (error >= 0 && error_msg[error])
		write(2, error_msg[error], ft_strlen(error_msg[error]));
	else
		write(2, "Unknown error\n", 14);
}

static void	destruction(t_data *data)
{
	if (data->back)
		mlx_destroy_image(data->mlx, data->back);
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->player)
		mlx_destroy_image(data->mlx, data->player);
	if (data->textures[0].img.img)
		mlx_destroy_image(data->mlx, data->textures[0].img.img);
	if (data->textures[1].img.img)
		mlx_destroy_image(data->mlx, data->textures[1].img.img);
	if (data->textures[2].img.img)
		mlx_destroy_image(data->mlx, data->textures[2].img.img);
	if (data->textures[3].img.img)
		mlx_destroy_image(data->mlx, data->textures[3].img.img);
	if (data->frame.img)
		mlx_destroy_image(data->mlx, data->frame.img);
	if (data->window)
	{
		mlx_clear_window(data->mlx, data->window);
		mlx_destroy_window(data->mlx, data->window);
	}
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
}

static void	cleanup_all(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx)
		destruction(data);
	free_data(data);
	free(data);
}

void	handle_error(t_errorlst error, t_data *data)
{
	char	*error_msg[42];

	error_msg[PARAMETROS] = "Error en los parametros!\n";
	error_msg[MALLOCERROR] = "Error Malloc!\n";
	error_msg[FD] = "Fallo en el fd!\n";
	error_msg[MLX_ERROR] = "MiniLibX no pudo abrir una ventana. Revisa el entorno grafico/display.\n";
	error_msg[IMG_ERROR] = "Error en las imagenes!\n";
	error_msg[CUB] = "It is not a .cub!\n";
	error_msg[CONFIG_ERROR] = "Faltan texturas o colores en el archivo .cub!\n";
	error_msg[COLOR_ERROR] = "Color invalido en el archivo .cub!\n";
	error_msg[NOTRECTANGULAR] = "El mapa no tiene la forma correcta!\n";
	error_msg[NOTWALLS] = "El mapa no esta rodeado de muros!\n";
	error_msg[INVALID_CHARS] = "Not correct characters!\n";
	error_msg[INVALID_PE] = "Not correct number of player!\n";
	error_msg[NOTPLAYER] = "No hay jugador!\n";
	error_msg[MAPERROR] = "Error de mapa!\n";
	print_errors(error, error_msg);
	cleanup_all(data);
	exit(1);
}

int	destroy_all(t_data *data)
{
	cleanup_all(data);
	exit(0);
	return (0);
}
