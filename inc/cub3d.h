/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/09 17:51:59 by jroth            ###   ########.fr       */
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

typedef struct s_data
{
	char	**map;	
}			t_data;

// PARSER
bool	parse_map(t_data *data, char *file);
bool	validate_map(char **map);

#endif
