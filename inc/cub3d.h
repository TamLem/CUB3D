/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/21 15:10:39 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../_MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
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

enum e_direction {
	north,
	south,
	east,
	west
};

# define WIDTH 1280
# define HEIGHT 768
# define PI 3.14159
# define CELL_WIDTH 32
# define CELL_HEIGHT 32
# define MOVE_SPEED 0.05

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_ray
{
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
    double	deltaDistX;
    double	deltaDistY;
    double	perpWallDist;
    int		stepX;
    int		stepY;
    int		hit;
    int		side;
}	t_ray;

typedef struct s_raycaster
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	oldDirX;
	double	oldDirY;
	double	planeX;
	double	oldPlaneX;
	double	planeY;
	double	oldPlaneY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	t_ray	ray;
}	t_raycaster;

typedef struct s_window
{
	bool		enable;
	void		*mlx;
	mlx_image_t	*window;
	mlx_image_t textures[4];
	t_raycaster	frame;
	int			c;
	int			f;
}	t_window;

typedef struct s_data
{
	char		**map;
	char		*txt_paths[5];
	mlx_texture_t *textures[5];
	t_window	window;
}	t_data;

// PARSER
bool	parse_map(t_data *data, char *file);
bool	validate_map(char **map, t_data *data);
bool	get_info(t_data *data);
bool	get_player_info(t_data *data);

// DRAW
void	init_window(t_data *data);
void	kill_window(t_window *window);
void	raycaster(t_data *data);
void	hook(void *param);
void	render(void *param);
void	move(t_data *data);
void	rotate_dir(t_data *data);
void	rotate(t_data *data);
int		create_trgb(int t, int r, int g, int b);
void	draw_ray(int x, t_window *window, t_raycaster *frame);

// UTILS
void	error_msg(char *msg, t_data *data);
void	free_2d(char **arr);
int		create_trgb(int t, int r, int g, int b);
bool	check_char(const char c);


#endif
