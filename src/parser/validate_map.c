/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:01 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 19:46:10 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_position(t_raycaster *frame, int k, int i)
{
	frame->pos_x = (double) k + 0.5;
	frame->pos_y = (double) i + 0.5;
	frame->dir_x = -1;
	frame->dir_y = 0;
	frame->plane_x = 0;
	frame->plane_y = 0.66;
}

static int	set_player(t_data *data, char **map, int k, int i)
{
	set_position(&data->window.frame, k, i);
	if (map[k][i] == 'S')
	{
		data->window.frame.dir_x = 1;
		data->window.frame.plane_y = -0.66;
	}
	else if (map[k][i] == 'W')
	{
		data->window.frame.dir_x = 0;
		data->window.frame.dir_y = -1;
		data->window.frame.plane_x = -0.66;
		data->window.frame.plane_y = 0;
	}
	else if (map[k][i] == 'E')
	{
		data->window.frame.dir_x = 0;
		data->window.frame.dir_y = 1;
		data->window.frame.plane_x = 0.66;
		data->window.frame.plane_y = 0;
	}
	map[k][i] = '0';
	return (1);
}

static bool	check_neighbours(char **map, int x, int y)
{
	if (map[y][x] && map[y][x] == '0')
	{
		if ((map[y][x + 1] && white_space(map[y][x + 1]))
			|| (map[y][x - 1] && white_space(map[y][x - 1]))
			|| (!map[y + 1][x] || white_space(map[y + 1][x]))
			|| (!map[y - 1][x]) || white_space(map[y - 1][x]))
			return (false);
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
				player += set_player(data, map, k, i);
			if (!check_char(map[k][i]) || !check_neighbours(map, i, k))
				error_msg("Invalid Map! Check chars and borders!", data);
		}	
		i = -1;
	}
	if (player != 1)
		error_msg("You have to set 1 (!) spawnpoint. (N,S,E,W)", data);
	return (true);
}

bool	validate_map(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (white_space(map[0][i]))
		i++;
	while (map[0][i])
	{
		if (map[0][i++] != '1')
			return (false);
	}
	if (check_chars(data, map))
		return (true);
	return (false);
}
