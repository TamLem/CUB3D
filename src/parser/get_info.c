/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 20:54:24 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	find_map_start(char ***map)
{
	char	**mapstart;

	while (*map && *(*map + 1) && !check_line(*(*map)))
		(*map)++;
	mapstart = *map;
	while (*mapstart)
	{
		if ((white_space(**mapstart) || **mapstart == '1') && **mapstart != '\n')
			mapstart++;
		else
			error_msg("Mapfile has to end with last line of Map!", NULL);
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
	int		i;
	char	*path;
	char	*pwd;

	i = 0;
	while (str[i] != '.')
		i++;
	i++;
	pwd = get_pwd(data->env);
	path = ft_strjoin(pwd, str + i);
	free(pwd);
	if (access(path, R_OK) != 0)
	{
		free(path);
		error_msg("Invalid TXT_PATH!", data);
	}
	if (!ft_strncmp(str, "N", 1))
		data->txt_paths[0] = path;
	else if (!ft_strncmp(str, "S", 1))
		data->txt_paths[1] = path;
	else if (!ft_strncmp(str, "E", 1))
		data->txt_paths[2] = path;
	else if (!ft_strncmp(str, "W", 1))
		data->txt_paths[3] = path;
}

bool	get_info(t_data *data)
{
	int	i;
	int	colors;

	if (!check_txt(data->map))
		error_msg("Put ONE of each: NO/SO/EA/WE ./path/to/texture", data);
	while (data->txt_paths[++i])
		data->txt_paths[i] = NULL;
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
	data->free_map = data->map;
	find_map_start(&data->map);
	return (true);
}
