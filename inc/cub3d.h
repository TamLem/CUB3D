/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 11:24:24 by tlemma           ###   ########.fr       */
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
# define MOVE_SPEED 0.1

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_player
{
	double x;
	double y;
	int		posX;
	int		posY;
	// float angle;
	// float fov;
}	t_player;

typedef struct s_ray
{
	//which box of the map we're in
      int mapX;
      int mapY;
      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;
       //length of ray from one x or y-side to next x or y-side
      double deltaDistX;
      double deltaDistY;
      double perpWallDist;
      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;
      int hit; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
}	t_ray;

typedef struct s_raycaster
{
	double	posX;
	double	posY;  //x and y start position
	double	dirX;
	double	dirY; //initial direction vector
	double	oldDirX;
	double	oldDirY;
	double	planeX;
	double	oldPlaneX;
	double	planeY; //the 2d raycaster version of camera plane
	double	oldPlaneY;
	double	time; //time of current frame
	double	oldTime; //time of previous frame
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
	t_raycaster	frame;
}	t_window;

typedef struct s_data
{
	char		**map;
	char		**txt_paths;
	t_window	window;
	t_player	player;
	t_color		c;
	t_color		f;
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


// int init(void);
// void	draw_xy_rays(int x0, int y0);
// void	draw_cell(mlx_image_t *img, int x, int y, int color);
// void	draw_line(mlx_image_t *win, int beginX, int beginY, int endX, int endY, int color);

// UTILS
void	error_msg(char *msg, t_data *data);
void	free_2d(char **arr);
int		find_map_start(char **map);
bool	isPointInFloor(int x, int y);
int	create_trgb(int t, int r, int g, int b);


#endif
