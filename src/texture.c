#include "../inc/cub3d.h"


void	load_texture(t_data *data)
{
	data->textures[0]  = mlx_load_png("/Users/tlemma/Documents/42-curcus_c/cub3d/textures/bricksx64.png");
// = mlx_texture_to_image(data->window.mlx, temp);

	if (data->textures[0] == NULL)
		printf("texture load error\n");

}