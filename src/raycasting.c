/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:17:17 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 14:05:20 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_loop(int x, t_raycaster *frame)
{
	t_ray	*ray;

	frame->camera_x = (double)(2 * x) / (double) WIDTH - 1;
	frame->raydir_x = frame->dir_x + (frame->plane_x * frame->camera_x);
	frame->raydir_y = frame->dir_y + (frame->plane_y * frame->camera_x);
	ray = &frame->ray;
	if (frame->raydir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1 / frame->raydir_x);
	if (frame->raydir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1 / frame->raydir_y);
	ray->map_x = (int) frame->pos_x;
	ray->map_y = (int) frame->pos_y;
}

void	calc_step_and_side_dist(t_raycaster	*frame)
{
	t_ray	*ray;

	ray = &frame->ray;
	ray->hit = 0;
	ray->step_x = 1;
	ray->side_dist_x = (ray->map_x + 1.0 - frame->pos_x)
		* ray->delta_dist_x;
	if (frame->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (frame->pos_x - ray->map_x) * ray->delta_dist_x;
	}
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - frame->pos_y)
		* ray->delta_dist_y;
	if (frame->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (frame->pos_y - ray->map_y) * ray->delta_dist_y;
	}
}

void	exec_dda(char **map, t_raycaster *frame)
{
	t_ray	*ray;

	ray = &frame->ray;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (frame->raydir_x < 0)
				ray->side = north;
			else
				ray->side = south;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (frame->raydir_y < 0)
				ray->side = west;
			else
				ray->side = east;
		}
		if (map[ray->map_x][ray->map_y] > '0')
			ray->hit = 1;
	}
	if (ray->side == north || ray->side == south)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
} 

void	kill_window(t_window *window)
{
	mlx_delete_image(window->mlx, window->window);
	mlx_terminate(window->mlx);
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
		calc_step_and_side_dist(frame);
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
