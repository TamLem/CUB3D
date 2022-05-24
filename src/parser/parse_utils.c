/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:39:10 by jroth             #+#    #+#             */
/*   Updated: 2022/05/24 17:57:47 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	check_valid_info(char *str)
{
	while (white_space(*str))
		str++;
	if (*str == '\0')
		return (true);
	if (*str == '1' || *str == '\n')
		return (true);
	else if (*str == 'C' || *str == 'F')
		return (true);
	else if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "EA", 2) || !ft_strncmp(str, "WE", 2))
		return (true);
	else if (*str == 'N' || *str == 'S'
		|| *str == 'E' || *str == 'W')
		return (false);
	return (false);
}

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
	if ((!ft_strncmp(data->map[i], "NO", 2))
		|| (!ft_strncmp(data->map[i], "SO", 2))
		|| (!ft_strncmp(data->map[i], "EA", 2))
		|| (!ft_strncmp(data->map[i], "WE", 2)))
		return (true);
	return (false);
}

bool	check_txt(char **map)
{
	int	txt[4];
	int	i;

	i = -1;
	while (++i < 4)
		txt[i] = 0;
	i = -1;
	while (map[++i])
	{
		if (map[i][0] == 'N'
			&& (map[i][1] == '.' || white_space(map[i][1]) || map[i][1] == 'O'))
			txt[0] += 1;
		if (map[i][0] == 'S'
			&& (map[i][1] == '.' || white_space(map[i][1]) || map[i][1] == 'O'))
			txt[1] += 1;
		if (map[i][0] == 'W'
			&& (map[i][1] == '.' || white_space(map[i][1]) || map[i][1] == 'E'))
			txt[2] += 1;
		if (map[i][0] == 'E'
			&& (map[i][1] == '.' || white_space(map[i][1]) || map[i][1] == 'A'))
			txt[3] += 1;
	}
	if (txt[0] != 1 || txt[1] != 1 || txt[2] != 1 || txt[3] != 1)
		return (false);
	return (true);
}

bool	check_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && (white_space(str[i]) || str[i] == '1'))
	{
		if (str[i] == '1')
			return (true);
	}
	return (false);
}
