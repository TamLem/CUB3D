/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 17:08:46 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

static int	find_color_cf(t_data *data, char *str)
{
	char	**colors;
	int		i;
	t_color	color;

	i = 0;
	colors = ft_split(str + 2, ',');
	while (colors[i])
		i++;
	if (i == 3)
	{
		color.red = ft_atoi(colors[0]);
		color.green = ft_atoi(colors[1]);
		color.blue = ft_atoi(colors[2]);
	}
	free_2d(colors);
	if (!check_colors(color))
		error_msg("Please use RBG values from 0-255!", data);
	if (str[0] == 'F' && data->window.f == -1)
		data->window.f = create_trgb(color.red, color.green, color.blue, 255);
	else if (str[0] == 'C' && data->window.c == -1)
		data->window.c = create_trgb(color.red, color.green, color.blue, 255);
	return (1);
}

static void	set_texture_path(t_data *data, char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		data->txt_paths[0] = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "N ", 2))
		data->txt_paths[0] = ft_strdup(str + 2);
	if (!ft_strncmp(str, "SO ", 3))
		data->txt_paths[1] = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "S ", 2))
		data->txt_paths[1] = ft_strdup(str + 2);
	if (!ft_strncmp(str, "EA ", 3))
		data->txt_paths[2] = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "E ", 2))
		data->txt_paths[2] = ft_strdup(str + 2);
	if (!ft_strncmp(str, "WE ", 3))
		data->txt_paths[3] = ft_strdup(str + 3);
	else if (!ft_strncmp(str, "W ", 2))
		data->txt_paths[3] = ft_strdup(str + 2);
}

bool	get_info(t_data *data)
{
	int	i;
	int	colors;

	colors = 0;
	i = -1;
	while (data->map[++i])
	{
		if (check_text_path(data, i))
			set_texture_path(data, data->map[i]);
		if (!ft_strncmp(data->map[i], "F", 1)
			|| !ft_strncmp(data->map[i], "C", 1))
			colors += find_color_cf(data, data->map[i]);
	}
	if (colors != 2 || (data->window.c == -1 || data->window.f == -1))
		error_msg("You have to set C AND F (only) once! ('C/F R,G,B')", data);
	find_map_start(&data->map);
	return (true);
}
