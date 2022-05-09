/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:05 by jroth             #+#    #+#             */
/*   Updated: 2022/05/09 20:57:38 by jroth            ###   ########.fr       */
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
		perror("Couldn't allocate mapdata.");
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
	{
		printf("Invalid Filename!\n");
		return (false);
	}
	if (str[i - 1] == 'b'
		&& str[i - 2] == 'u'
		&& str[i - 3] == 'c'
		&& str[i - 4] == '.')
		return (true);
	printf("Invalid Extension!\n");
	return (false);
}

static int	find_map_start(char **map)
{
	int	i;

	i = 0;
	while (map[i][0] != '1')
		i++;
	return (i);
}

bool	parse_map(t_data *data, char *file)
{
	if (!check_extension(file))
		return (false);
	data->map = return_map(file);
	if (validate_map(data->map + find_map_start(data->map)))
		return (true);
	printf("Invalid Map!\n");
	return (false);
}
