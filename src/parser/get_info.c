/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 14:08:54 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	check_line(char *str)
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

static void	find_map_start(char ***map)
{
	while (*map)
	{
		if (check_line(*(*map + 1)))
		{
			free(**map);
			**map = NULL;
			(*map)++;
			break ;
		}
		free(**map);
		**map = NULL;
		(*map)++;
	}
}

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
	free_2d(colors);
	if ((color.red < 0 || color.red > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.blue < 0 || color.blue > 255))
		error_msg("Please use RBG values from 0-255!", data);
	if (str[0] == 'F')
		data->window.f = create_trgb(color.red, color.green, color.blue, 255);
	else if (str[0] == 'C')
		data->window.c = create_trgb(color.red, color.green, color.blue, 255);
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
	find_map_start(&data->map);
	return (true);
}
