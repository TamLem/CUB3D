/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:17:17 by jroth             #+#    #+#             */
/*   Updated: 2022/05/17 21:56:00 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

typedef struct s_ray
{
	//which box of the map we're in
      int mapX;
      int mapY;
      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;
       //length of ray from one x or y-side to next x or y-side
      double deltaDistX;
      double deltaDistY;
      double perpWallDist;
      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;
      int hit; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
}	t_ray;

typedef struct s_raycaster
{
	double	posX;
	double	posY;  //x and y start position
	double	dirX;
	double	dirY; //initial direction vector
	double	planeX;
	double	planeY; //the 2d raycaster version of camera plane
	double	time; //time of current frame
	double	oldTime; //time of previous frame
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	t_ray	ray;
}	t_raycaster;

void	set_loop(int x, t_raycaster *frame)
{
	t_ray	*ray;

	frame->cameraX = 2 * x / (double) WIDTH - 1;
	frame->rayDirX = frame->dirX + frame->planeX * frame->cameraX;
	frame->rayDirY = frame->dirY + frame->planeY * frame->cameraX;
	ray = &frame->ray;
	if (frame->rayDirX == 0)
		ray->deltaDistX = INFINITY;
	else
		ray->deltaDistX = fabs(1 / frame->rayDirX);
	if (frame->rayDirY == 0)
		ray->deltaDistY = INFINITY;
	else
		ray->deltaDistY = fabs(1 / frame->rayDirY);
	ray->mapX = frame->posX;
	ray->mapX = frame->posY;
}

void	init_frame(t_raycaster *frame)
{
	frame->posX = g_data.player.posX;
	frame->posY = g_data.player.posY;
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
	ray->hit = 0;
	while (ray->hit == 0)
    {
      //jump to next map square, either in x-direction, or in y-direction
      	if (ray->sideDistX < ray->sideDistY)
      	{
      		ray->sideDistX += ray->deltaDistX;
			printf("DistX %f\n", ray->sideDistX);
			printf("DeltaX %f\n", ray->deltaDistX);
      	  	ray->mapX += ray->stepX;
			printf("MapX %d\n", ray->mapX);
      		ray->side = 0;
      	}
      	else
      	{
      	  	ray->sideDistY += ray->deltaDistY;
			printf("DistY %f\n", ray->sideDistY);
			printf("DeltaY %f\n", ray->deltaDistY);
      	  	ray->mapY += ray->stepY;
			printf("MapY %d\n", ray->mapY);
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

// void draw_vert_line(t_window *window, int x, int beginY, int endY, int color)
// {
// 	int line;

// 	line = window->lineHeight;
// 	while (line)
// 	{
// 		mlx_put_pixel(window->window, x, pixelY, 0xFFFFFFFF);
// 	   	--line;
// 	}
// }

void	hook(void *param)
{
	t_window	*window;

	window = param;
	if (mlx_is_key_down(window->mlx, MLX_KEY_ESCAPE))
	{
		window->enable = false;
		mlx_close_window(window->mlx);
	}
}

void	kill_window(t_window *window)
{
	mlx_delete_image(window->mlx, window->window);
	mlx_terminate(window->mlx);
}

void	init_window(t_window *window)
{
	window->enable = true;
	window->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D!", false);
	if (!window->mlx)
		exit(-1);
	window->window = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->window, 0, 0);
	mlx_loop_hook(window->mlx, &hook, window);	
}

void	draw_window(int x, t_window *window, t_raycaster *frame)
{
	int	h;
	h = HEIGHT;
    //Calculate height of line to draw on screen
	if (frame->ray.perpWallDist > 0)
    	window->lineHeight = (int) (h / frame->ray.perpWallDist);
	else
		window->lineHeight = 0;
    //calculate lowest and highest pixel to fill in current stripe
    window->drawStart = -(window->lineHeight) / 2 + h / 2;
    if (window->drawStart < 0)
		window->drawStart = 0;
    window->drawEnd = window->lineHeight / 2 + h / 2;
    if (window->drawEnd >= h)
		window->drawEnd = h - 1;
	// draw_line(window->window, window->drawStart, , window->drawStart, window->drawEnd, 0xFFFFFFFF);
	// printf("%d -> Start: %d End: %d linheight: %d\n", x, window->drawStart, window->drawEnd, window->lineHeight);
	// void	draw_line_vert(t_window *window, int x, int color)
	
	// while (window->drawStart < window->drawEnd)
	// 	mlx_put_pixel(window->window, x, window->drawStart++, 0xFFFFFFFF);
	while (window->lineHeight--)
	{
		if (frame->ray.side == 0)
			mlx_put_pixel(window->window, x, window->drawStart++, 0xFFFFFFFF);
		else
			mlx_put_pixel(window->window, x, window->drawStart++, 0xAAFFFFFF);
	}	
		
}

void	raycaster(void)
{
	t_raycaster	frame;
	t_window	window;

	init_window(&window);
	init_frame(&frame);
	int x = -1;
	printf("x:%f y:%f\n", frame.posX, frame.posY);
	while (window.enable == true)
	{
		while (++x < WIDTH)
		{
			set_loop(x, &frame);
			calc_step_and_sideDist(&frame);
			exec_dda(g_data.map + find_map_start(g_data.map), &frame);
			draw_window(x, &window, &frame);
			// double oldDirX = frame.dirX;
      		// frame.dirX = frame.dirX * cos(-0.2) - frame.dirY * sin(-0.2);
      		// frame.dirY = oldDirX * sin(-0.2) + frame.dirY * cos(-0.2);
      		// double oldPlaneX = frame.planeX;
      		// frame.planeX = frame.planeX * cos(-0.2) - frame.planeY * sin(-0.2);
      		// frame.planeY = oldPlaneX * sin(-0.2) + frame.planeY * cos(-0.2);
		}
		usleep(500);
		mlx_loop(window.mlx);
	}
}
