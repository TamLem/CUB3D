/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 11:47:00 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	bool	check_colors(t_data *data)
{
	t_color	c;
	t_color	f;

	c = data->c;
	f = data->f;
	if ((f.red > -1 && f.green > -1 && f.blue > -1
			&& c.red > -1 && c.green > -1 && c.blue > -1)
		&& (f.red < 256 && f.green < 256 && f.blue < 256
			&& c.red < 256 && c.green < 256 && c.blue < 256))
		return (true);
	error_msg("Wrong color Values! (0-255)", data);
	return (false);
}

static void	find_color_cf(t_data *data, char *str)
{
	char	**colors;
	int		i;

	i = 0;
	colors = ft_split(str + 2, ',');
	while (colors[i])
		i++;
	if (i != 3)
	{
		free_2d(colors);
		error_msg("Wrong color format! 'C/F R,G,B'", data);
	}
	if (str[0] == 'C')
	{
		data->c.red = ft_atoi(colors[0]);
		data->c.green = ft_atoi(colors[1]);
		data->c.blue = ft_atoi(colors[2]);
	}
	if (str[0] == 'F')
	{
		data->f.red = ft_atoi(colors[0]);
		data->f.green = ft_atoi(colors[1]);
		data->f.blue = ft_atoi(colors[2]);
	}
	free_2d(colors);
}

static void	set_texture_path(t_data *data, char *str)
{
	// if (!data->txt_paths)
	// 	data->txt_paths = malloc(sizeof(char *) * 5);
	if (!ft_strncmp(str, "NO ", 3))
		data->txt_paths[0] = ft_strdup(str + 3);
	if (!ft_strncmp(str, "SO ", 3))
		data->txt_paths[1] = ft_strdup(str + 3);
	if (!ft_strncmp(str, "EA ", 3))
		data->txt_paths[2] = ft_strdup(str + 3);
	if (!ft_strncmp(str, "WE ", 3))
		data->txt_paths[3] = ft_strdup(str + 3);
}

bool	get_info(t_data *data)
{
	int	i;

	i = -1;
	while (data->map[++i])
	{
		if (!ft_strncmp(data->map[i], "NO ", 3)
			|| !ft_strncmp(data->map[i], "SO ", 3)
			|| !ft_strncmp(data->map[i], "EA ", 3)
			|| !ft_strncmp(data->map[i], "WE ", 3))
			set_texture_path(data, data->map[i]);
		if (!ft_strncmp(data->map[i], "F ", 2)
			|| !ft_strncmp(data->map[i], "C ", 2))
			find_color_cf(data, data->map[i]);
	}
	i = -1;
	while (data->txt_paths[++i])
	{
		if (!access(data->txt_paths[i], R_OK)) // change as soon was we have textures
			error_msg("Textures couldn't be loaded", data);
	}
	if (i != 4 || !check_colors(data))
		return (false);
	return (true);
}

// float get_angle(char angle)
// {
// 	if (angle == 'N')
// 		return(0.5 * PI);
// 	if (angle == 'E')
// 		return(0);
// 	if (angle == 'S')
// 		return(1.5 * PI);
// 	else
// 		return(PI);
// }

// bool get_player_info(t_data *data)
// {
// 	int			i;
// 	int			j;
// 	char 		**map;
// 	t_player	*player;

// 	i = 0;
// 	map = data->map + find_map_start(data->map);
// 	player = &data->player;
// 	while (i < data->size.y)
// 	{
// 		j = 0;
// 		while (j < data->size.x)
// 		{
// 			if (ft_strchr("NESW", map[i][j]) != NULL)
// 			{
// 				player->x = j * CELL_WIDTH;
// 				player->y = i * CELL_HEIGHT;
// 				player->posX = j;
// 				player->posY = i;
// 				// player->angle = get_angle(map[i][j]);
// 				return (true);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("Player not found in map\n");
// 	return (false);
// }
