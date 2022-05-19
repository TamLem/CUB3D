/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:31:39 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 12:23:30 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hook(void *param)
{
	t_data		*data;
	t_window	*window;
	t_raycaster	*frame;
	double		rotSpeed = 0.05;
	double		moveSpeed = 1.0;

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
