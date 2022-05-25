/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/25 16:41:55 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	find_map_start(char ***map, t_data *data)
{
	char	**mapstart;

	while (*map && *(*map + 1) && !check_line(**map))
	{
		if (check_valid_info(**map))
			(*map)++;
		else
			error_msg("Invalid specification characters found!", NULL);
	}
	mapstart = *map;
	while (*mapstart)
	{
		if (**mapstart && (white_space(**mapstart) || **mapstart == '1'))
			mapstart++;
		else
			error_msg("Mapfile has to end with Map!", data);
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
		error_msg("Invalid color format! (e.g. 'C/F 0,127,255')", data);
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
		path = NULL;
		error_msg("Invalid TXT_PATH!", data);
	}
	if (!ft_strncmp(str, "NO", 2))
		data->txt_paths[0] = path;
	else if (!ft_strncmp(str, "SO", 2))
		data->txt_paths[1] = path;
	else if (!ft_strncmp(str, "EA", 2))
		data->txt_paths[2] = path;
	else if (!ft_strncmp(str, "WE", 2))
		data->txt_paths[3] = path;
}

bool	get_info(t_data *data)
{
	int	i;
	int	colors;

	i = -1;
	if (!check_txt(data->map))
		error_msg("Put ONE (!) of each: NO/SO/EA/WE ./path/to/texture", data);
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
	{
		printf("here1 %d %d\n", data->window.c, data->window.f);
		error_msg("Invalid color format! (e.g. 'C/F 0,127,255')", data);
	}
	find_map_start(&data->map, data);
	return (true);
}
