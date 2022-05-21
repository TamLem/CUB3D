/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:01 by jroth             #+#    #+#             */
/*   Updated: 2022/05/20 17:17:33 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

void	set_position(t_raycaster *frame, int k, int i)
{
	frame->posX = (double) k + 0.5;
	frame->posY = (double) i + 0.5;
	frame->dirX = -1;
	frame->dirY = 0;
	frame->planeX = 0;
	frame->planeY = 0.66;
}

static int	set_player(t_data *data, char **map, int k, int i)
{
	set_position(&data->window.frame, k , i);
	if (map[k][i] == 'S')
	{
		data->window.frame.dirX = 1;
		data->window.frame.planeY = -0.66;
	}
	else if (map[k][i] == 'W')
	{
		data->window.frame.dirX = 0;
		data->window.frame.dirY = -1;
		data->window.frame.planeX = -0.66;
		data->window.frame.planeY = 0;
	}
	else if (map[k][i] == 'E')
	{
		data->window.frame.dirX = 0;
		data->window.frame.dirY = 1;
		data->window.frame.planeX = 0.66;
		data->window.frame.planeY = 0;
	}
	map[k][i] = '0';
	return (1);
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
				player +=  set_player(data, map, k, i);
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
