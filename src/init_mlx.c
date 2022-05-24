/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:31:39 by jroth             #+#    #+#             */
/*   Updated: 2022/05/24 19:03:06 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	load_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures[i] = mlx_load_png(data->txt_paths[i]);
		if (data->textures[i] == NULL)
		{
			while (--i >= 0)
				mlx_delete_texture(data->textures[i]);
			error_msg("Couldn't load textures!", data);
			return (false);
		}
		i++;
	}
	return (true);
}

void	init_window(t_data *data)
{
	t_window	*window;

	window = &data->window;
	window->enable = true;
	window->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D!", false);
	if (!window->mlx)
		exit(-1);
	window->window = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->window, 0, 0);
}

void	key_input(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;

	window = &data->window;
	frame = &window->frame;
	if (mlx_is_key_down(window->mlx, MLX_KEY_ESCAPE))
	{
		window->enable = false;
		mlx_close_window(window->mlx);
	}
	move(data);
	rotate(data);
}
