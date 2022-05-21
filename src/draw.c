#include "../inc/cub3d.h"


int	get_texture(t_raycaster *frame)
{
	if (frame->ray.side == north)
		return (0);
	else if (frame->ray.side == south)
		return (1);
	else if (frame->ray.side == east)
		return (2);
	else
		return (3);
}

#define texHeight 64
#define texWidth 64

void	texturize(t_data *data, int x, int drawStart, int drawEnd)
{
	t_raycaster	*frame;
	double		wallX;
	int			texX;
	int			tex_id;
	
	frame = &data->window.frame;
	tex_id = get_texture(frame);
	if (frame->ray.side == 0 || frame->ray.side == 1)
		wallX = frame->posY + frame->ray.perpWallDist * frame->rayDirY;
	else
		wallX = frame->posX + frame->ray.perpWallDist * frame->rayDirX;
	wallX -= floor((wallX));

	texX = (int)(wallX * (double)texWidth);
	if ((frame->ray.side == 0 && frame->rayDirX > 0) || (frame->ray.side == 1 && frame->rayDirY < 0) )
		texX = texWidth - texX - 1;

	int		lineHeight = drawEnd - drawStart;
	double	step = 1.0 * texHeight / lineHeight;

	double textPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
	int	y = drawStart;
	while (y < drawEnd)
	{
		int texY = (int)textPos & (texHeight - 1);
		textPos += step;
		uint8_t *pixelx = &data->textures[tex_id]->pixels[((texY) * data->textures[tex_id]->width + (texX)) * 4];
		// mlx_put_pixel(data->window.window, x, y, *pixelx);
		uint8_t	*pixeli = &data->window.window->pixels[((y * data->window.window->width + x) * 4)];
		memmove(pixeli, pixelx, 4);
		y++;
	}
}

void	draw_ray(int x, t_data *data, t_raycaster *frame)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	t_window *window;

	lineHeight = 0;
	drawStart = 0;
	drawEnd = 0;
	window = &data->window;
	if (frame->ray.perpWallDist > 0)
    	lineHeight = (int) (HEIGHT / frame->ray.perpWallDist);
	else
		lineHeight = 0;
    drawStart = -(lineHeight) / 2 + HEIGHT / 2;
    if (drawStart < 0)
		drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	int i = 0;
	texturize(data, x, drawStart, drawEnd);
	while (i < HEIGHT)
	{
		if (i >= drawStart && i <= drawEnd)
		{
			// if (frame->ray.side == north)
			// 	mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFEE);
			// else if (frame->ray.side == south)
			// 	mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFAA);
			// else if (frame->ray.side == east)
			// 	mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFCC);
			// else if (frame->ray.side == west)
			// 	mlx_put_pixel(window->window, x, drawStart++, 0xFFFFFFDD);
		}
		else if (i < drawStart)
			mlx_put_pixel(window->window, x, i, window->c);
		else
			mlx_put_pixel(window->window, x, i, window->f);
		i++;
	}
}
