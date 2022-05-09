/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:01 by jroth             #+#    #+#             */
/*   Updated: 2022/05/09 18:05:49 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// TODO:
// COUNT PLAYER CHARS == 1
// CHECK LENGTHS ARE CONSISTENT
// CHECK BORDERS

static bool	check_char(const char c)
{
	if (c == '1' || c == '0'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	validate_map(char **map)
{
	int	player;
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++y])
	{
		// printf("%s\n", map[y]);
		while (map[y][++x])
		{
			if (!check_char(map[y][x]))
				return (false);
		}	
		x = -1;
	}
	return (true);
}