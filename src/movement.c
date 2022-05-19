#include "../inc/cub3d.h"

void	move_player(float move_dirX, float move_dirY, t_data *data)
{
    t_raycaster	*frame;
	char		**map;

    frame = &data->window.frame;
	map = data->map + find_map_start(data->map);
	// printf("x_cell: %d, y_cell %d, posX %f, posY %f\n", x_cell, y_cell, frame->posX, frame->posY);
	if(map[(int)(frame->posX + move_dirX * MOVE_SPEED)][(int)frame->posY] == '0')
		frame->posX += move_dirX * MOVE_SPEED;
	if(map[(int)(frame->posX)][(int)(frame->posY + move_dirY * MOVE_SPEED)] == '0')
		frame->posY += move_dirY * MOVE_SPEED;
}

void	move(t_data *data)
{
	float		dirX;
	float		dirY;
	mlx_t		*mlx;
	double		rotSpeed;

	mlx = data->window.mlx;
	dirX = data->window.frame.dirX;
	dirY = data->window.frame.dirY;
// printf("x:%f y:%f\n", data->window.frame.posX, data->window.frame.posY);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(dirY, -dirX, data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(-dirY, dirX, data);
	if (mlx_is_key_down(mlx, MLX_KEY_S) )
		move_player(-dirX, -dirY, data);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(dirX, dirY, data);
}

void	rotate_dir(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;
	double		rotSpeed = 0.05;

	window = &data->window;
	frame = &window->frame;
	frame->dirX = frame->dirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
	frame->dirY = frame->oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
	frame->planeX = frame->planeX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
	frame->planeY = frame->oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
	// printf("oldDirX: %f newDirX:%f\n", frame->oldDirX, frame->dirX);
}


void	rotate(t_data *data)
{
	t_window	*window;
	t_raycaster	*frame;
	double		rotSpeed;

	window = &data->window;
	frame = &window->frame;
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		rotSpeed = 0.05;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		rotSpeed = -0.05;
	frame->oldDirX = frame->dirX;
	frame->dirX = frame->dirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
	frame->dirY = frame->oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
	frame->oldPlaneX = frame->planeX;
	frame->planeX = frame->planeX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
	frame->planeY = frame->oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
}