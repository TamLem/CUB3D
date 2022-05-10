#include "../inc/cub3d.h"

mlx_image_t	*g_img;
mlx_image_t *img_player;

#define CELL_WIDTH 16
#define CELL_HEIGHT 16

bool	isPointInFloor(int x, int y)
{
	int x_cell;
	int y_cell;
	char	**map;

	map = g_data.map + find_map_start(g_data.map);
	x_cell = x / CELL_WIDTH;
	y_cell = y / CELL_HEIGHT;
	printf("x: %d y: %d\n", x_cell, y_cell);
	if (map[y_cell][x_cell] == '0')
	{
		printf("true\n");
		return (true);
	}
	return (false);
}


void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP)
		&& isPointInFloor(img_player->instances[0].x, img_player->instances[0].y - 5))
		img_player->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN) 
		&& isPointInFloor(img_player->instances[0].x, img_player->instances[0].y + 5))
		img_player->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT) 
		&& isPointInFloor(img_player->instances[0].x - 5, img_player->instances[0].y))
		img_player->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT)
		&& isPointInFloor(img_player->instances[0].x + 5, img_player->instances[0].y))
		img_player->instances[0].x += 5;
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

void	draw_map(mlx_image_t *img, t_data *data)
{
	int	i;
	int	j;
	char	**map;
	
	map = data->map + find_map_start(data->map);
	i = 0;
	while (i < 44)
	{
		j = 0;
		while (j < 30)
		{
			if (map[i][j] == '1')
				draw_cell(img, j*CELL_WIDTH, i*CELL_HEIGHT, 0xFFFFFF);
			if (map[i][j] == '0')
				draw_cell(img, j*CELL_WIDTH, i*CELL_HEIGHT, 0);
			j++;
		}
		i++;
	}
}



void	put_player(void * mlx)
{
	img_player = mlx_new_image(mlx, 10, 10);
	memset(img_player->pixels, 255, img_player->width * img_player->height * sizeof(int));
	mlx_image_to_window(mlx, img_player, 100, 100);
}

int init(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!mlx)
		exit(1);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	draw_map(g_img, &g_data);
	put_player(mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_terminate(mlx);

	return (0);
}