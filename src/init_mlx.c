/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:31:39 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 15:31:38 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	mlx_loop_hook(window->mlx, &hook, data);
}

void	hook(void *param)
{
	t_data		*data;
	t_window	*window;
	t_raycaster	*frame;

	data = param;
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
