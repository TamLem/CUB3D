/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/09 22:43:58 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	bool	check_colors(t_data *data)
{
	t_color	c;
	t_color	f;

	c = data->c;
	f = data->f;
	if (f.red > -1 && f.green > -1 && f.blue > -1
		&& c.red > -1 && c.green > -1 && c.blue > -1)
		return (true);
	printf("Wrong Color Format!\n");
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
	i = -1;
	while (colors[++i])
		free(colors[i]);
	free(colors);
	colors = NULL;
}

static void	set_texture_path(t_data *data, char *str)
{
	if (!data->txt_paths)
		data->txt_paths = malloc(sizeof(char *) * 5);
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
	i = 0;
	while (data->txt_paths[i])
		i++;
	if (i != 4 || !check_colors(data))
		return (false);
	return (true);
}
