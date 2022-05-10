/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/10 15:53:59 by jroth            ###   ########.fr       */
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
}	t_vec;

typedef struct s_data
{
	mlx_t	*mlx;
	char	**map;
	char	**txt_paths;
	t_vec	size;
	t_color	c;
	t_color	f;
}	t_data;

t_data	g_data;

// PARSER
bool	parse_map(t_data *data, char *file);
bool	validate_map(char **map, t_data *data);
bool	get_info(t_data *data);

// DRAW
int init(void);

// UTILS
void	error_msg(char *msg, t_data *data);
void	free_2d(char **arr);
int		find_map_start(char **map);

#endif
