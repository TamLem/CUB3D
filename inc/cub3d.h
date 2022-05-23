/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 13:55:44 by tlemma           ###   ########.fr       */
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
# define X 0
# define Y 1
# define BPP 4

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_raycaster
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	olddir_x;
	double	olddir_y;
	double	plane_x;
	double	oldplane_x;
	double	plane_y;
	double	oldplane_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	t_ray	ray;
}	t_raycaster;

typedef struct s_window
{
	bool		enable;
	void		*mlx;
	mlx_image_t	*window;
	t_raycaster	frame;
	int			c;
	int			f;
}	t_window;

typedef struct s_data
{
	char			**map;
	char			*txt_paths[4];
	mlx_texture_t	*textures[4];
	t_window		window;
	char			*pwd;
}				t_data;

// PARSER
bool	parse_map(t_data *data, char *file);
bool	validate_map(char **map, t_data *data);
bool	get_info(t_data *data);
bool	get_player_info(t_data *data);

// WINDOW AND MLX
void	init_window(t_data *data);
void	kill_window(t_window *window);
void	hook(void *param);
void	render(void *param);

//RAY CASTING AND PLAYER MOVEMENT
void	raycaster(t_data *data);
void	move(t_data *data);
void	rotate_dir(t_data *data);
void	rotate(t_data *data);

//draw
bool	load_texture(t_data *data);
void	draw_ray(int x, t_data *data, t_raycaster *frame);

// UTILS
void	error_msg(char *msg, t_data *data);
void	free_2d(char **arr);
int		create_trgb(int t, int r, int g, int b);
bool	check_char(const char c);
void	free_textures(t_data *data);
int		create_trgb(int t, int r, int g, int b);

#endif
