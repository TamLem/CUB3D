/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 17:59:41 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	find_color_cf(t_data *data, char *str)
{
	char	**colors;
	int		i;
	t_color	color;
	i = 0;
	colors = ft_split(str + 2, ',');
	while (colors[i])
		i++;
	if (i != 3)
	{
		free_2d(colors);
		error_msg("Wrong color format! 'C/F R,G,B'", data);
	}
	color.red = ft_atoi(colors[0]);
	color.green = ft_atoi(colors[1]);
	color.blue = ft_atoi(colors[2]);
	if ((color.red < 0 || color.red > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.blue < 0 || color.blue > 255))
		error_msg("Please use RBG values from 0-255!", data);
	if (str[0] == 'F')
		data->window.f = create_trgb(255, color.red, color.green, color.blue);
	else if (str[0] == 'C')
		data->window.c = create_trgb(255, color.red, color.green, color.blue);
	free_2d(colors);
}

static void	set_texture_path(t_data *data, char *str)
{

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

	data->txt_paths = malloc(sizeof(char *) * 5);
	if (!data->txt_paths)
		error_msg("Malloc Error!", data);
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
	i = 0;
	while (i < 4)
	{
		if (!data->txt_paths[i++])
			error_msg("Wrong number of Textures!", data);
	}
	return (true);
}
//  || !check_colors(data)
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
