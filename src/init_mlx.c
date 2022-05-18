/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:31:39 by jroth             #+#    #+#             */
/*   Updated: 2022/05/18 17:12:29 by jroth            ###   ########.fr       */
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
	// if (mlx_is_key_down(window->mlx, MLX_KEY_DOWN))
	// {
	// 	if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   	f(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	// }



	// void	move_player(int x_dir, int y_dir)
// {
// 	char		**map;
// 	t_player	*player;

// 	player = &g_data.player;
// 	map = g_data.map + find_map_start(g_data.map);
// 	if (map[((player->y + y_dir)) / 32][((player->x + x_dir)) / 32] != '1')
// 	{
// 		g_data.player_img->instances[0].y += y_dir;
// 		player->y += y_dir;
// 		g_data.player_img->instances[0].x += x_dir;
// 		player->x += x_dir;
// 	}
// }

	if (mlx_is_key_down(window->mlx, MLX_KEY_DOWN))
	{
      	if(data->map[(int)(frame->posX - (frame->dirX * moveSpeed))][(int)frame->posY] == '0')
		  	frame->posX -= frame->dirX * moveSpeed;
      	if(data->map[(int)(frame->posX)][(int)(frame->posY - (frame->dirY * moveSpeed))] == '0')
			frame->posY -= frame->dirY * moveSpeed;
		printf("%f\n", frame->posX);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
	{
      	frame->oldDirX = frame->dirX;
      	frame->dirX = frame->dirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
      	frame->dirY = frame->oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
      	frame->oldPlaneX = frame->planeX;
      	frame->planeX = frame->planeX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
      	frame->planeY = frame->oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
		printf("oldDirX: %f newDirX:%f\n", frame->oldDirX, frame->dirX);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
	{
		// printf("Left\n");
      	frame->oldDirX = frame->dirX;
      	frame->dirX = frame->dirX * cos(rotSpeed) - frame->dirY * sin(rotSpeed);
      	frame->dirY = frame->oldDirX * sin(rotSpeed) + frame->dirY * cos(rotSpeed);
      	frame->oldPlaneX = frame->planeX;
      	frame->planeX = frame->planeX * cos(rotSpeed) - frame->planeY * sin(rotSpeed);
      	frame->planeY = frame->oldPlaneX * sin(rotSpeed) + frame->planeY * cos(rotSpeed);
	}
}
