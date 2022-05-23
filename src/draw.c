/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/05/23 14:25:08 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static double	get_wall_x(t_raycaster *frame)
{
	double	wall_x;

	if (frame->ray.side == 0 || frame->ray.side == 1)
		wall_x = frame->pos_y + frame->ray.perp_wall_dist * frame->raydir_y;
	else
		wall_x = frame->pos_x + frame->ray.perp_wall_dist * frame->raydir_x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

static int	get_tex_x(t_raycaster *frame, mlx_texture_t *texture)
{
	int	tex_x;

	tex_x = (int)(get_wall_x(frame) * (double)texture->width);
	if ((frame->ray.side == 0 && frame->raydir_x > 0)
		|| (frame->ray.side == 1 && frame->raydir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

static void	texturize(t_data *data, int x, int draw_start, int draw_end)
{
	int				tex[2];
	int				line_height;
	double			step;
	double			text_pos;
	mlx_texture_t	*texture;

	texture = data->textures[data->window.frame.ray.side];
	tex[X] = get_tex_x(&data->window.frame, texture);
	line_height = draw_end - draw_start;
	step = 1.0 * texture->height / line_height;
	text_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	while (draw_start < draw_end)
	{
		tex[Y] = (int)text_pos & (texture->height - 1);
		text_pos += step;
		ft_memmove(&data->window.window->pixels[
			((draw_start * data->window.window->width + x) * BPP)],
			&texture->pixels[((tex[Y]) * texture->height + (tex[X])) * BPP],
			BPP);
		draw_start++;
	}
}

void	draw_ray(int x, t_data *data, t_raycaster *frame)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			i;
	t_window	*window;

	window = &data->window;
	line_height = 0;
	if (frame->ray.perp_wall_dist > 0)
		line_height = (int)(HEIGHT / frame->ray.perp_wall_dist);
	draw_start = -(line_height) / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	texturize(data, x, draw_start, draw_end);
	i = -1;
	while (++i < HEIGHT)
	{
		if (i < draw_start)
			mlx_put_pixel(window->window, x, i, window->c);
		if (i > draw_end)
			mlx_put_pixel(window->window, x, i, window->f);
	}
}
