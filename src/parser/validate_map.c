/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:01 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 19:38:56 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	check_char(const char c)
{
	if (c == '1' || c == '0'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

static bool	check_format(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++y])
	{	
		while (map[y][++x])
		{
			if ((map[y][x] == '0' && map[y][x + 1] && map[y][x + 1] == ' ')
				|| (map[y][x] == '0' && map[y][x - 1] && map[y][x - 1] == ' ')
				|| (map[y][x] == '0' && map[y + 1][x] && map[y + 1][x] == ' ')
				|| (map[y][x] == '0' && map[y - 1][x] && map[y - 1][x] == ' '))
				return (false);
		}
		x = -1;	
	}
	return (true);
}

static bool	check_chars(t_data *data, char **map)
{
	int	player;
	int	i;
	int	k;

	i = -1;
	k = -1;
	player = 0;
	while (map[++k])
	{
		while (map[k][++i])
		{
			if (map[k][i] == 'N' || map[k][i] == 'S'
				|| map[k][i] == 'E' || map[k][i] == 'W')
			{
				map[k][i] = '0';
				player++;
				data->player.posX = k;
				data->player.posY = i;
			}
			if (!check_char(map[k][i]))
				error_msg("Invalid characters found! (N,S,E,W,1,0)", data);
		}	
		i = -1;
	}
	if (player != 1)
		error_msg("You have to set 1 (!) spawnpoint. (N,S,E,W)", data);	
	return (true);
}

bool	validate_map(char **map, t_data *data)
{
	if (check_chars(data, map) && check_format(map))
		return (true);
	error_msg("A Problem occured with parsing the map!", data);
	return (false);
}
