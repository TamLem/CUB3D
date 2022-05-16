/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:05 by jroth             #+#    #+#             */
/*   Updated: 2022/05/16 15:52:40 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_line_count(char *file)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	count = 1;
	line = get_next_line(fd);
	if (!line)
		error_msg("File is empty. Please enter valid map information.", NULL);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

static char	**return_map(char *file)
{
	char	**mapdata;
	char	*line;
	int		i;
	int		fd;

	mapdata = malloc(sizeof(char *) * (get_line_count(file)));
	if (!mapdata)
		return (NULL);
	fd = open(file, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		mapdata[i++] = line;
		line = get_next_line(fd);
	}
	mapdata[i] = NULL;
	close(fd);
	return (mapdata);
}

static bool	check_extension(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i <= 4)
		return (false);
	if (str[i - 1] == 'b'
		&& str[i - 2] == 'u'
		&& str[i - 3] == 'c'
		&& str[i - 4] == '.')
		return (true);
	return (false);
}

bool	parse_map(t_data *data, char *file)
{
	if (!check_extension(file) || access(file, R_OK))
	{
		error_msg("Mapfile has to be available and end with .cub", data);
		return (false);
	}
	data->map = return_map(file);
	data->f.green = -1;
	data->f.red = -1;
	data->f.blue = -1;
	data->c.green = -1;
	data->c.red = -1;
	data->c.blue = -1;
	if (data->map && get_info(data)
		&& (validate_map(data->map + find_map_start(data->map), data)) && get_player_info())
		return (true);
	return (false);
}
