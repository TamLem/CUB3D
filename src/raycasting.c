/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:17:17 by jroth             #+#    #+#             */
/*   Updated: 2022/05/20 17:08:32 by jroth            ###   ########.fr       */
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
      		ray->side = 0;
      	}
      	else
      	{
      	  	ray->sideDistY += ray->deltaDistY;
      	  	ray->mapY += ray->stepY;
      	  	ray->side = 1;
      	}
		if (map[ray->mapX][ray->mapY] > '0')
			ray->hit = 1;
    }
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
} 

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
			if (frame->ray.side == 0)
				mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFFF);
			else
				mlx_put_pixel(window->window, x, drawStart++, 0xAAFFFFFF);
		}
		else if (i < drawStart)
			mlx_put_pixel(window->window, x, i, window->f);
		else
			mlx_put_pixel(window->window, x, i, window->c);
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
		draw_ray(x, &data->window, frame);
		x++;
	}
}

void	raycaster(t_data *data)
{
	t_raycaster	*frame;

	frame = &data->window.frame;
	init_window(data);
	printf("x:%f y:%f\n", frame->posX, frame->posY);
	while (data->window.enable == true)
	{
		mlx_loop_hook(data->window.mlx, &render, (data));
		mlx_loop(data->window.mlx);
	}
}
