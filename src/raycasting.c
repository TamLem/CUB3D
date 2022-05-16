/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:17:17 by jroth             #+#    #+#             */
/*   Updated: 2022/05/16 20:51:16 by jroth            ###   ########.fr       */
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


void	init_frame(t_raycaster *frame)
{
	frame->posX = g_data.player.x / CELL_WIDTH;
	frame->posY = g_data.player.y / CELL_HEIGHT;
	frame->dirX = -1;
	frame->dirY = 0;
	frame->planeX = 0;
	frame->planeY = 0.66;
	frame->time = 0;
	frame->oldTime = 0;
	frame->cameraX = 0;
	frame->rayDirX = 0;
	frame->rayDirY = 0;
}

void	set_ray(t_raycaster *frame)
{
	t_ray	*ray;

	ray = &frame->ray;
	ray->deltaDistX = fabs(1 / frame->rayDirX);
	ray->deltaDistY = fabs(1 / frame->rayDirY);
	ray->mapX = frame->posX;
	ray->mapX = frame->posY;
	
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

void	exec_dda(int i, char **map, t_raycaster *frame)
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
      	  	ray->mapX += ray->stepX;
      		ray->side = 0;
      	}
      	else
      	{
      	  ray->sideDistY += ray->deltaDistY;
      	  ray->mapY += ray->stepY;
      	  ray->side = 1;
      	}
		mlx_put_pixel(g_data.map_img, ray->mapX * CELL_WIDTH, ray->mapY * CELL_HEIGHT, 0xFFFFFFFF);
      	//Check if ray has hit a wall
		// printf("ray no: %d: map[%d][%d] == '%c'\n",i, ray->mapY, ray->mapX, map[ray->mapY][ray->mapX]);
		// printf("%d....\nSX: %f SY: %f \nmapX: %d mapY: %d \ndeltaX: %f deltaY: %f\n",i, ray->sideDistX, ray->sideDistY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistX);
		if (map[ray->mapX][ray->mapY] == '1')
		{
			mlx_put_pixel(g_data.map_img, ray->mapX * CELL_WIDTH, ray->mapY * CELL_HEIGHT, 0xFF00FF00);
			ray->hit = 1;
			printf("%d...\nY: %d\nX: %d\n",i, ray->mapY, ray->mapX);
			ray->mapX = (int) g_data.player.posX;
			ray->mapY = (int) g_data.player.posY;
		}
    }
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	// printf("%d:\t%f - %f = %f\n", i, ray->sideDistX, ray->deltaDistX, ray->perpWallDist);
}

void	raycaster(void)
{
	t_raycaster	frame;
	t_ray	ray;

	init_frame(&frame);
	int x = -1;
	int w = 45;
	// while (true)
	// {
		while (++x < w)
		{
			frame.cameraX = 2 * x / (double) w - 1;
			frame.rayDirX = frame.dirX + frame.planeX * frame.cameraX;
			frame.rayDirY = frame.dirY + frame.planeY * frame.cameraX;
			set_ray(&frame);
			calc_step_and_sideDist(&frame);
			exec_dda(x, g_data.map + find_map_start(g_data.map), &frame);
		}
}
