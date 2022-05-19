/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:17:17 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 19:29:42 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_loop(int x, t_raycaster *frame)
{
	t_ray	*ray;

	frame->cameraX = (double) (2 * x) / (double) WIDTH - 1;
	frame->rayDirX = frame->dirX + (frame->planeX * frame->cameraX);
// printf("rayDirX(%f) = dirX(%f) +  (planeX(%f) * cameraX(%f)\n", frame->rayDirX, frame->dirX, frame->planeX, frame->cameraX);
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
// printf("%d......\nCamera:\t\t%f\nrayDirX:\t%f\nrayDirY:\t%f\nrayDeltaX:\t%f\nrayDeltaY:\t%f\n",x, frame->cameraX, frame->rayDirX, frame->rayDirY, frame->ray.deltaDistX, frame->ray.deltaDistY);
}

void	init_frame(t_data *data, t_raycaster *frame)
{
	frame->posX = data->player.posX + 0.5;
	frame->posY = data->player.posY + 0.5;
	printf("%f, %f\n", frame->posX, frame->posY);
	frame->dirX = -1;
	frame->dirY = 0;
	frame->planeX = 0;
	frame->planeY = 0.66;
	// frame->time = 0;
	// frame->oldTime = 0;
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
// printf("X: if  %f = %f - %d * %f\n", ray->sideDistX, frame->posX, ray->mapX, ray->deltaDistX);
    }
    else
    {
    	ray->stepX = 1;
    	ray->sideDistX = (ray->mapX + 1.0 - frame->posX) * ray->deltaDistX;
// printf("X: else %f = %d - %f * %f\n", ray->sideDistX, ray->mapX, frame->posX, ray->deltaDistX);   
    }
    if (frame->rayDirY < 0)
    {
      	ray->stepY = -1;
      	ray->sideDistY = (frame->posY - ray->mapY) * ray->deltaDistY;
// printf("Y: if  %f = %f - %d * %f\n", ray->sideDistY, frame->posY, ray->mapY, ray->deltaDistY);

    }
    else
    {
      	ray->stepY = 1;
      	ray->sideDistY = (ray->mapY + 1.0 - frame->posY) * ray->deltaDistY;
// printf("Y: else %f = %d - %f * %f\n", ray->sideDistX, ray->mapX, frame->posX, ray->deltaDistX);
    }
// printf("x: %f y: %f\n", ray->sideDistX, ray->sideDistY);
}

void	exec_dda(char **map, t_raycaster *frame)
{

	t_ray	*ray;

	ray = &frame->ray;
	while (ray->hit == 0)
    {
      //jump to next map square, either in x-direction, or in y-direction
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
      	// Check if ray has hit a wall
		if (map[ray->mapX][ray->mapY] > '0')
			ray->hit = 1;
    }
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
} 

void	kill_window(t_window *window)
{
	mlx_delete_image(window->mlx, window->window);
	mlx_terminate(window->mlx);
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

void	draw_window(int x, t_window *window, t_raycaster *frame)
{
    //Calculate height of line to draw on screen
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
    //calculate lowest and highest pixel to fill in current stripe
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

// int	mlx_hooks(t_vars *vars)
// {
// 	mlx_hook(vars->mlx_vars->win_ptr, 17, 0, &exit_hook, vars);
// 	mlx_hook(vars->mlx_vars->win_ptr, 2, 0, &on_key_down, vars);
// 	mlx_hook(vars->mlx_vars->win_ptr, 3, 0, &on_key_up, vars);
// 	mlx_loop_hook(vars->mlx_vars->mlx_ptr, &update, vars);
// 	mlx_loop(vars->mlx_vars->mlx_ptr);
// 	return (0);
// }

void	render(void *param)
{
	t_data		*data;
	t_raycaster	*frame;
	int			x;
	
	data = (t_data *) param;
	// data->map += find_map_start(data->map);
	frame = &data->window.frame;
	x = 0;
	while (x < WIDTH)
	{	
		set_loop(x, frame);
		calc_step_and_sideDist(frame);
		exec_dda(data->map + find_map_start(data->map), frame);
		draw_window(x, &data->window, frame);
		x++;
	}
}

void	raycaster(t_data *data)
{
	t_raycaster	*frame;

	// data->map += find_map_start(data->map);
	frame = &data->window.frame;
	init_window(data);
	init_frame(data, frame);
	printf("x:%f y:%f\n", frame->posX, frame->posY);
	printf("player[%d][%d]\n", data->player.posX, data->player.posY);
	while (data->window.enable == true)
	{
		mlx_loop_hook(data->window.mlx, &render, (data));
		mlx_loop(data->window.mlx);
	}
}
