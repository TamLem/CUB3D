/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/16 19:16:58 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../_MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <math.h>	
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <memory.h>

enum e_error {
	mapfile = 5,
	map_err,
	fc,
	txt,
	mllc
};

# define WIDTH 1280
# define HEIGHT 768
# define PI 3.14159
# define CELL_WIDTH 32
# define CELL_HEIGHT 32

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_vec
{
	int	x;
	int y;
	int map_x0;
	int map_y0;
}	t_vec;

typedef struct s_player
{
	int	x;
	int y;
	double	posX;
	double  posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	int height;
	float angle;
	float fov;
}	t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*map_img;
	mlx_image_t *player_img;
	char		**map;
	char		**txt_paths;
	t_player	player;
	t_vec		size;
	t_color		c;
	t_color		f;
}	t_data;

t_data	g_data;

// PARSER
bool	parse_map(t_data *data, char *file);
bool	validate_map(char **map, t_data *data);
bool	get_info(t_data *data);
bool	get_player_info();

// DRAW
int init(void);
void	draw_xy_rays(int x0, int y0);
void	draw_cell(mlx_image_t *img, int x, int y, int color);

void	raycaster(void);

// UTILS
void	error_msg(char *msg, t_data *data);
void	free_2d(char **arr);
int		find_map_start(char **map);
bool	isPointInFloor(int x, int y);
int	create_trgb(int t, int r, int g, int b);


#endif
