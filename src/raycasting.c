/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:17:17 by jroth             #+#    #+#             */
/*   Updated: 2022/05/21 16:16:23 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_loop(int x, t_raycaster *frame)
{
	t_ray	*ray;

	frame->cameraX = (double) (2 * x) / (double) WIDTH - 1;
	frame->rayDirX = frame->dirX + (frame->planeX * frame->cameraX);
	frame->rayDirY = frame->dirY + (frame->planeY * frame->cameraX);
	ray = &frame->ray;
	if (frame->rayDirX == 0)
		ray->deltaDistX = INFINITY;
	else
		ray->deltaDistX = fabs(1 / frame->rayDirX);
	if (frame->rayDirY == 0)
		ray->deltaDistY = INFINITY;
	else
		ray->deltaDistY = fabs(1 / frame->rayDirY);
	ray->mapX = (int) frame->posX;
	ray->mapY = (int) frame->posY;
}

void	calc_step_and_sideDist(t_raycaster	*frame)
{
	t_ray	*ray;

	ray = &frame->ray;
	ray->hit = 0;
	if (frame->rayDirX < 0)
    {
      	ray->stepX = -1;
      	ray->sideDistX = (frame->posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
    	ray->stepX = 1;
    	ray->sideDistX = (ray->mapX + 1.0 - frame->posX) * ray->deltaDistX;
    }
    if (frame->rayDirY < 0)
    {
      	ray->stepY = -1;
      	ray->sideDistY = (frame->posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
      	ray->stepY = 1;
      	ray->sideDistY = (ray->mapY + 1.0 - frame->posY) * ray->deltaDistY;
    }
}

void	exec_dda(char **map, t_raycaster *frame)
{
	t_ray	*ray;

	ray = &frame->ray;
	while (ray->hit == 0)
    {
      	if (ray->sideDistX < ray->sideDistY)
      	{
      		ray->sideDistX += ray->deltaDistX;
      	  	ray->mapX += ray->stepX;
			if (frame->rayDirX < 0)
				ray->side = north;
			else
      			ray->side = south;
      	}
      	else
      	{
      	  	ray->sideDistY += ray->deltaDistY;
      	  	ray->mapY += ray->stepY;
			if (frame->rayDirY < 0)
      	  		ray->side = west;
			else
				ray->side = east;
      	}
		if (map[ray->mapX][ray->mapY] > '0')
			ray->hit = 1;
    }
	if (ray->side == north || ray->side == south)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
} 

void	kill_window(t_window *window)
{
	mlx_delete_image(window->mlx, window->window);
	mlx_terminate(window->mlx);
}


void	draw_window(int x, t_data *data, t_raycaster *frame)
{
    //Calculate height of line to draw on screen
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	t_window *window;

	window = &data->window;
	lineHeight = 0;
	drawStart = 0;
	drawEnd = 0;
	if (frame->ray.perpWallDist > 0)
    	lineHeight = (int) (HEIGHT / frame->ray.perpWallDist);
	else
		lineHeight = 0;
    //calculate lowest and highest pixel to fill in current stripe
    drawStart = -(lineHeight) / 2 + HEIGHT / 2;
    if (drawStart < 0)
		drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	int i = 0;
	texturize(data, x, drawStart, drawEnd);
	// drawStart += drawEnd - drawStart;
	while (i < HEIGHT)
	{
		if (i >= drawStart && i <= drawEnd)
		{

			// mlx_put_pixel(window->window, x, i, 0x00000000);
				// mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFFF);
			// if (frame->ray.side == 0)
			// 	draw_texture(data, x, drawStart++);
			// else
			// 	mlx_put_pixel(window->window, x, drawStart++, 0xAAFFFFFF);

		}
		else if (i < drawStart)
			mlx_put_pixel(window->window, x, i, 0x0000FF77);
		else if (i > drawEnd)
		{
			mlx_put_pixel(window->window, x, i, 0x00FF0077);
		}
		i++;
	}
}

void	render(void *param)
{
	t_data		*data;
	t_raycaster	*frame;
	int			x;
	
	data = (t_data *) param;
	frame = &data->window.frame;
	x = 0;
	while (x < WIDTH)
	{	
		set_loop(x, frame);
		calc_step_and_sideDist(frame);
		exec_dda(data->map, frame);
		draw_ray(x, data, frame);
		x++;
	}
}

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
