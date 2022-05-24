/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:18:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/24 16:57:40 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, t_data *data)
{
	printf("ERROR!\n%s\n", msg);
	exit(-1);
}

void	cursor_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->window.enable = false;
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(data->txt_paths[i]);
		mlx_delete_texture(data->textures[i]);
		i++;
	}
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
