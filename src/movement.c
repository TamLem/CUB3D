/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:03:56 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 16:37:57 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	check_wall(float move_dir_x, float move_dir_y, t_data *data)
{
	int				i;
	t_raycaster		*frame;
	char			**map;

	i = 1;
	frame = &data->window.frame;
	map = data->map;
	while (i < 400 * MOVE_SPEED)
	{
		if ((map[(int)(frame->pos_x + move_dir_x * i * MOVE_SPEED)]
			[(int)frame->pos_y] == '1') ||
			(map[(int)(frame->pos_x)]
			[(int)(frame->pos_y + move_dir_y * i * MOVE_SPEED)] == '1'))
			return (false);
		i++;
	}
	return (true);
}

void	move_player(float move_dir_x, float move_dir_y, t_data *data)
{
	t_raycaster		*frame;
	char			**map;

	frame = &data->window.frame;
	map = data->map;
	if (check_wall(move_dir_x, move_dir_y, data))
	{
		frame->pos_x += move_dir_x * MOVE_SPEED;
		frame->pos_y += move_dir_y * MOVE_SPEED;
	}
}

void	move(t_data *data)
{
	float		dir_x;
	float		dir_y;
	mlx_t		*mlx;
	double		rot_speed;
	t_raycaster	*frame;

	mlx = data->window.mlx;
	dir_x = data->window.frame.dir_x;
	dir_y = data->window.frame.dir_y;
	frame = &data->window.frame;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(dir_y, -dir_x, data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(-dir_y, dir_x, data);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(-dir_x, -dir_y, data);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(dir_x, dir_y, data);
}

void	rotate_dir(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;
	double		rot_speed;

	rot_speed = 0.05;
	window = &data->window;
	frame = &window->frame;
	frame->dir_x = frame->dir_x
		* cos(-rot_speed) - frame->dir_y * sin(-rot_speed);
	frame->dir_y = frame->olddir_x
		* sin(-rot_speed) + frame->dir_y * cos(-rot_speed);
	frame->plane_x = frame->plane_x
		* cos(-rot_speed) - frame->plane_y * sin(-rot_speed);
	frame->plane_y = frame->oldplane_x
		* sin(-rot_speed) + frame->plane_y * cos(-rot_speed);
}

void	rotate(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;
	double		rot_speed;

	window = &data->window;
	frame = &window->frame;
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		rot_speed = 0.05;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		rot_speed = -0.05;
	frame->olddir_x = frame->dir_x;
	frame->dir_x = frame->dir_x
		* cos(-rot_speed) - frame->dir_y * sin(-rot_speed);
	frame->dir_y = frame->olddir_x
		* sin(-rot_speed) + frame->dir_y * cos(-rot_speed);
	frame->oldplane_x = frame->plane_x;
	frame->plane_x = frame->plane_x
		* cos(-rot_speed) - frame->plane_y * sin(-rot_speed);
	frame->plane_y = frame->oldplane_x
		* sin(-rot_speed) + frame->plane_y * cos(-rot_speed);
}
