#include "../inc/cub3d.h"

bool	ray_checker(int x, int y)
{
	int 	x_cell;
	int 	y_cell;
	char	**map;
	double	dirX = -1;
	double	dirY = 0;
	double	planeX = 0, planeY = 0.66;
	double	time = 0;
	double	oldTime = 0;
	map = g_data.map + find_map_start(g_data.map);
	x_cell = x / CELL_WIDTH;
	y_cell = y / CELL_HEIGHT;
	printf("xpx: %d ypx: %d map[%d][%d]\n",x,y,y_cell, x_cell);
	if (map[y_cell][x_cell] == '1')
		return (false);
	return (true);
}

void 	draw_xy_rays(int x0, int y0)
{
	mlx_image_t	*map_img;
	int			i = 0;
	float		distance;
	float		angle;

	map_img = g_data.map_img;
	while (ray_checker(x0, y0))
	{
		mlx_put_pixel(map_img, x0, y0, create_trgb(255, 255, 255, 0));

		x0++;
		y0++;
		i++;
	}
	// printf("ray tip; %d %d\n", x0, y0);
}

void draw_xzyz_rays()
{

}

void	cast_rays()
{

}