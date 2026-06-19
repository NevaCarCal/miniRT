/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:29:57 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:30:11 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		handle_error(PARAMETROS, NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		handle_error(MALLOCERROR, NULL);
	ft_memset(data, 0, sizeof(t_data));
	ft_init(data, argv);
	game_init(data);
	destroy_all(data);
	return (0);
}
