/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:03:56 by jroth             #+#    #+#             */
/*   Updated: 2022/05/22 18:06:41 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	check_wall(float move_dirX , float move_dirY, t_data *data)
{
	int	i;
	t_raycaster		*frame;
	char			**map;

	i = 1;
	frame = &data->window.frame;
	map = data->map;
	while (i < 400 * MOVE_SPEED)
	{
		if ((map[(int)(frame->posX + move_dirX * i * MOVE_SPEED)][(int)frame->posY] == '1') ||
			(map[(int)(frame->posX)][(int)(frame->posY + move_dirY * i * MOVE_SPEED)] == '1') )
				return (false);
		i++;
	}
	return (true);
}

void	move_player(float move_dirX, float move_dirY, t_data *data)
{
	t_raycaster		*frame;
	char			**map;

	frame = &data->window.frame;
	map = data->map;
	if (check_wall(move_dirX, move_dirY, data))
		{
			frame->posX += move_dirX * MOVE_SPEED;
			frame->posY += move_dirY * MOVE_SPEED;
		}
}

void	move(t_data *data)
{
	float		dirX;
	float		dirY;
	mlx_t		*mlx;
	double		rotSpeed;

	mlx = data->window.mlx;
	dirX = data->window.frame.dirX;
	dirY = data->window.frame.dirY;
	t_raycaster *frame;
	frame = &data->window.frame;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(dirY, -dirX, data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(-dirY, dirX, data);
	if (mlx_is_key_down(mlx, MLX_KEY_S) )
		move_player(-dirX, -dirY, data);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(dirX, dirY, data);
}

void	rotate_dir(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;
	double		rotSpeed = 0.05;

	window = &data->window;
	frame = &window->frame;
	frame->dirX = frame->dirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
	frame->dirY = frame->oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
	frame->planeX = frame->planeX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
	frame->planeY = frame->oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
}

void	rotate(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;
	double		rotSpeed;

	window = &data->window;
	frame = &window->frame;
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		rotSpeed = 0.05;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		rotSpeed = -0.05;
	frame->oldDirX = frame->dirX;
	frame->dirX = frame->dirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
	frame->dirY = frame->oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
	frame->oldPlaneX = frame->planeX;
	frame->planeX = frame->planeX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
	frame->planeY = frame->oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
}