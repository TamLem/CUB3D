/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:46:38 by jroth             #+#    #+#             */
/*   Updated: 2022/05/15 19:44:58 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


bool	isPointInFloor(int x, int y)
{
	int 	x_cell;
	int 	y_cell;
	char	**map;

	map = g_data.map + find_map_start(g_data.map);
	x_cell = (x - g_data.size.map_x0) / CELL_WIDTH;
	y_cell =(y - g_data.size.map_y0) / CELL_HEIGHT;
	if (map[y_cell][x_cell] == '1')
	{
		printf("xpx: %d ypx: %d map[%d][%d]\n",x,y,y_cell, x_cell);
		return (false);
	}
	return (true);
}

void	move_player(int x_dir, int y_dir)
{
	char		**map;
	t_player	*player;

	player = &g_data.player;
	map = g_data.map + find_map_start(g_data.map);
	if (map[((player->y + y_dir)) / 32][((player->x + x_dir)) / 32] != '1')
	{
		g_data.player_img->instances[0].y += y_dir;
		player->y += y_dir;
		g_data.player_img->instances[0].x += x_dir;
		player->x += x_dir;
	}
}

void	hook(void *param)
{
	mlx_t		*mlx;
	mlx_image_t	*player_img;
	int	px;

	px = 2;
	player_img = g_data.player_img;
	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		move_player(0, -px);
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		move_player(0, px);
	if (mlx_is_key_down(param, MLX_KEY_LEFT) )
		move_player(-px, 0);
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		move_player(px, 0);
}

void	draw_cell(mlx_image_t *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	//check for image boundaries
	while (i < CELL_HEIGHT - 1)
	{
		j = 0;
		while (j < CELL_WIDTH - 1)
		{
			mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_map(mlx_image_t *img, t_data *data)
{
	int	i;
	int	j;
	char	**map;
	
	map = data->map + find_map_start(data->map);
	i = 0;
	while (i < g_data.size.y)
	{
		j = 0;
		while (j < g_data.size.x)
		{
			if (map[i][j] == '1')
				draw_cell(img, j*CELL_WIDTH, i*CELL_HEIGHT, create_trgb(255, 255, 255, 255));
			if (map[i][j] == '0' || ft_strchr("NESW", map[i][j]) != NULL)
				draw_cell(img, j*CELL_WIDTH, i*CELL_HEIGHT, create_trgb(255, 50, 50, 50));
			j++;
		}
		i++;
	}
}



void	put_player()
{
	mlx_t		*mlx;
	mlx_image_t	*player_img;

	mlx = g_data.mlx;
	g_data.player_img = mlx_new_image(mlx, 10, 10);
	player_img = g_data.player_img;
	memset(player_img->pixels, 255, player_img->width * player_img->height * sizeof(int));
	mlx_image_to_window(mlx, player_img, (g_data.player.x - 5) + g_data.size.map_x0, (g_data.player.y - 5) + g_data.size.map_y0);
}

void print_map_details()
{
	printf("player position x:%d,  y:%d\n", g_data.player.x, g_data.player.y);
	printf("map start: %d - %d\n map end: %d - %d\n", g_data.size.map_x0, g_data.size.map_x0 + g_data.size.x * CELL_WIDTH, g_data.size.map_y0, g_data.size.map_y0 + g_data.size.y * CELL_HEIGHT);
}

int init(void)
{
	void		*mlx;

	g_data.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	mlx = g_data.mlx;
	if (!mlx)
		exit(1);
 	print_map_details();
	g_data.map_img = mlx_new_image(mlx, g_data.size.x * CELL_WIDTH, g_data.size.y * CELL_HEIGHT);
	mlx_image_to_window(mlx, g_data.map_img, g_data.size.map_x0, g_data.size.map_y0);
	draw_map(g_data.map_img, &g_data);
	put_player();
	// printf("playerx %d\nplayery%d\nmapx0 %d\nmapy0 %d\n",g_data.player.x, g_data.size.map_x0, g_data.player.y, g_data.size.map_y0);
	// draw_xy_rays(g_data.player.x, g_data.player.y);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_data.map_img);
	mlx_terminate(mlx);
	return (0);
}