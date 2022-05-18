#include "../inc/cub3d.h"

void	move_player(float move_dirX, float move_dirY, t_data *data)
{
    t_raycaster	*frame;
	int			x_cell;
	int			y_cell;
	char		**map;

    frame = &data->window.frame;
	map = data->map + find_map_start(data->map);
	// x_cell = frame->posX + x_dir * MOVE_SPEED;
	// y_cell = frame->posY + y_dir * MOVE_SPEED;
	printf("x_cell: %d, y_cell %d, posX %f, posY %f\n", x_cell, y_cell, frame->posX, frame->posY);
	if(map[(int)(frame->posX + move_dirX * MOVE_SPEED)][(int)frame->posY] == '0')
		frame->posX += move_dirX * MOVE_SPEED;
	if(map[(int)(frame->posX)][(int)(frame->posY + move_dirY * MOVE_SPEED)] == '0')
		frame->posY += move_dirY * MOVE_SPEED;
}

void	move(mlx_t *mlx, t_data *data)
{
	int	px;
	float	dirX;
	float	dirY;

	px = 1;
	dirX = data->window.frame.dirX;
	dirY = data->window.frame.dirY;
	// printf("dir x: %f, dir y %f\n", dirX, dirY);

	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(dirY, -dirX, data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(-dirY, dirX, data);
	if (mlx_is_key_down(mlx, MLX_KEY_S) )
		move_player(-dirX, -dirY, data);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(dirX, dirY, data);
}