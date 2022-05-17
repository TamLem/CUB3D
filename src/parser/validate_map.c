/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:01 by jroth             #+#    #+#             */
/*   Updated: 2022/05/17 21:47:47 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	check_char(const char c)
{
	if (c == '1' || c == '0'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (true);
	return (false);
}

static bool	check_format(char **map)
{
	int	len;
	int	x;
	int	y;

	x = -1;
	y = -1;
	len = ft_strlen(map[y + 1]);
	while (map[++y])
	{	
		if (y == 0 || !map[y + 1])
		{
			while (map[y][++x])
			{
				if (map[y][x] != '1')
					return (false);
			}
			x = -1;
		}	
		if (map[y][0] != '1' || map[y][len - 1] != '1'
			|| ft_strlen(map[y]) != len)
			return (false);
	}
	g_data.size.x = len;
	g_data.size.y = y;
	return (true);
}

static bool	check_chars(char **map)
{
	int	player;
	int	x;
	int	y;

	x = -1;
	y = -1;
	player = 0;
	while (map[++y])
	{
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				// g_data.player.posX = x;
				// g_data.player.posY = y;
				player++;
			}
			if (!check_char(map[y][x]))
				error_msg("Invalid characters found! (N,S,E,W,1,0)", &g_data);
		}	
		x = -1;
	}
	if (player != 1)
		error_msg("You have to set 1 (!) spawnpoint. (N,S,E,W)", &g_data);	
	return (true);
}

bool	validate_map(char **map, t_data *data)
{
	if (check_chars(map) && check_format(map))
		return (true);
	error_msg("A Problem occured with parsing the map!", data);
	return (false);
}
