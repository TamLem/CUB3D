/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:18:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 17:09:06 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	raycaster(t_data *data)
{
	t_raycaster	*frame;

	frame = &data->window.frame;
	init_window(data);
	while (data->window.enable == true)
	{
		mlx_loop_hook(data->window.mlx, &render, (data));
		mlx_loop(data->window.mlx);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		error_msg(
			"Please execute with './cub3D path/to/map/MAPNAME.cub'.", &data);
	}
	else if (parse_map(&data, argv[1]) && load_texture(&data))
		raycaster(&data);
	else
		error_msg("A Problem occured with parsing the mapfile!", &data);
	return (0);
}
