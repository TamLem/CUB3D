#include "../inc/cub3d.h"

// bool	ray_checker(void)
// {
// 	int 	x_cell;
// 	int 	y_cell;
// 	char	**map;

// 	int x = g_data.player.x;
// 	int y = g_data.player.y;
// 	map = g_data.map + find_map_start(g_data.map);
// 	x_cell = (x - g_data.size.map_x0) / CELL_WIDTH;
// 	y_cell =(y - g_data.size.map_y0) / CELL_HEIGHT;
// 	printf("xpx: %d ypx: %d map[%d][%d]\n",x,y,y_cell, x_cell);
// 	if (map[y_cell][x_cell] == '1')
// 		return (false);
// 	return (true);
// }

void 	draw_xy_rays(int x0, int y0)
{
	mlx_image_t	*map_img;
	int i = 0;

	map_img = g_data.map_img;
	while (isPointInFloor(x0, y0))
	{
		// printf("x0: %d, y0: %d\n", x0, y0);
		mlx_put_pixel(map_img, x0, y0, create_trgb(255, 255, 255, 255));

		x0++;
		y0++;
		i++;
	}
	printf("ray tip; %d %d\n", x0, y0);
}

void draw_xzyz_rays()
{

}

void	cast_rays()
{

}