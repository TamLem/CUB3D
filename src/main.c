/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:18:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/24 19:53:43 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cursor_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->window.enable = false;
}

void	init_data(t_data *data)
{
	data->free_map = NULL;
	data->txt_paths[0] = NULL;
	data->txt_paths[1] = NULL;
	data->txt_paths[2] = NULL;
	data->txt_paths[3] = NULL;
}

void	raycaster(t_data *data)
{
	t_raycaster	*frame;

	frame = &data->window.frame;
	init_window(data);
	mlx_close_hook(data->window.mlx, &cursor_close, data);
	while (data->window.enable)
	{
		mlx_loop_hook(data->window.mlx, &render, (data));
		mlx_loop(data->window.mlx);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.env = env;
	init_data(&data);
	if (argc != 2)
	{
		error_msg(
			"Please execute with './cub3D path/to/map/MAPNAME.cub'.", &data);
	}
	else if (parse_map(&data, argv[1]) && load_texture(&data))
		raycaster(&data);
	else
		error_msg("A Problem occured with parsing the mapfile!", &data);
	cub_exit(&data);
	return (0);
}
