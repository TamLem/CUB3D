/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:29:06 by jroth             #+#    #+#             */
/*   Updated: 2022/05/10 15:35:47 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i++])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
}

int	find_map_start(char **map)
{
	int	i;

	i = 0;
	while (map[i][0] != '1')
		i++;
	return (i);
}

void	error_msg(char *msg, t_data *data)
{
	printf("ERROR!\n%s\n", msg);
	if (data)
	{
		if (data->map)
			free(data->map);
		if (data->txt_paths)
			free(data->txt_paths);
	}
	exit(-1);
}
