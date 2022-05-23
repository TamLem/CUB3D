/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:05 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 20:01:11 by jroth            ###   ########.fr       */
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

char	*get_pwd(char **env)
{
	char	*ret;

	while (*env)
	{
		if (!ft_strncmp(*env, "PWD=", 4))
		{
			ret = ft_strdup(*env + 4);
			break ;
		}
		env++;
	}
	return (ret);
}

bool	parse_map(t_data *data, char *file)
{
	if (!check_extension(file) || access(file, R_OK) != 0)
	{
		error_msg("Mapfile has to be available and end with .cub", data);
		return (false);
	}
	data->map = return_map(file);
	data->window.c = -1;
	data->window.f = -1;
	if (data->map && get_info(data)
		&& (validate_map(data->map, data)))
		return (true);
	return (false);
}
