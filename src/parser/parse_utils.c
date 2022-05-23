/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:39:10 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 16:55:43 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	check_colors(t_color color)
{
	if ((color.red < 0 || color.red > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.blue < 0 || color.blue > 255))
		return (false);
	return (true);
}

bool	check_text_path(t_data *data, int i)
{
	if ((!ft_strncmp(data->map[i], "NO", 2)
			|| !ft_strncmp(data->map[i], "N", 1))
		|| (!ft_strncmp(data->map[i], "SO", 2)
			|| !ft_strncmp(data->map[i], "S", 1))
		|| (!ft_strncmp(data->map[i], "EA", 2)
			|| !ft_strncmp(data->map[i], "E", 1))
		|| (!ft_strncmp(data->map[i], "WE", 2))
		|| !ft_strncmp(data->map[i], "W", 1))
		return (true);
	return (false);
}

bool	check_neighbours(char **map, int x, int y)
{
	if (map[y][x] == '0')
	{
		if ((map[y][x + 1] && map[y][x + 1] == ' ')
			|| (map[y][x - 1] && map[y][x - 1] == ' ')
			|| (!map[y + 1][x] || map[y + 1][x] == ' ')
			|| (!map[y - 1][x]) || map[y - 1][x] == ' ')
			return (false);
	}
	return (true);
}

bool	check_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && (str[i] == ' ' || str[i] == '1'))
	{
		if (str[i] == '1')
			return (true);
	}
	return (false);
}
