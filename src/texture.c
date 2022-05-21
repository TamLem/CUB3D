#include "../inc/cub3d.h"


bool	load_texture(t_data *data)
{
	data->textures[0]  = mlx_load_png("/Users/tlemma/Documents/42-curcus_c/cub3d/textures/bricksx64.png");
	data->textures[1]  = mlx_load_png("/Users/tlemma/Documents/42-curcus_c/cub3d/textures/bluestone.png");
	data->textures[2]  = mlx_load_png("/Users/tlemma/Documents/42-curcus_c/cub3d/textures/mossy.png");
	data->textures[3]  = mlx_load_png("/Users/tlemma/Documents/42-curcus_c/cub3d/textures/greystone.png");

	if (data->textures[0] == NULL || data->textures[1] == NULL 
		|| data->textures[2] == NULL || data->textures[3] == NULL)
		{
			printf("texture load error\n");
			return (false);
		}
	return (true);
}