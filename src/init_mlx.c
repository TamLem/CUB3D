/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:31:39 by jroth             #+#    #+#             */
/*   Updated: 2022/05/21 15:06:38 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray(int x, t_window *window, t_raycaster *frame)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;

	lineHeight = 0;
	drawStart = 0;
	drawEnd = 0;
	if (frame->ray.perpWallDist > 0)
    	lineHeight = (int) (HEIGHT / frame->ray.perpWallDist);
	else
		lineHeight = 0;
    drawStart = -(lineHeight) / 2 + HEIGHT / 2;
    if (drawStart < 0)
		drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	int i = 0;
	while (i < HEIGHT)
	{
		if (i >= drawStart && i <= drawEnd)
		{
			if (frame->ray.side == north)
				mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFEE);
			else if (frame->ray.side == south)
				mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFAA);
			else if (frame->ray.side == east)
				mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFCC);
			else if (frame->ray.side == west)
				mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFDD);
		}
		else if (i < drawStart)
			mlx_put_pixel(window->window, x, i, window->c);
		else
			mlx_put_pixel(window->window, x, i, window->f);
		i++;
	}
}

void	init_window(t_data *data)
{
	t_window *window;

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
