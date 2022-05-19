/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:29:06 by jroth             #+#    #+#             */
/*   Updated: 2022/05/19 15:39:50 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// int	decode_trgb(int color)
// {
// 	return (((color >> 24) & 0xFF), ((color >> 16) & 0xFF), 
// 			((color >> 8) & 0xFF), (color  & 0xFF));
// }
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
	while (map[i] && map[i][0] != '1')
		i++;
	return (i);
}

void	error_msg(char *msg, t_data *data)
{
	printf("ERROR!\n%s\n", msg);
	if (data)
	{
		if (data->map)
			free_2d(data->map);
		// if (data->txt_paths) //changed texture array to static array, free elements instead
		// 	free_2d(data->txt_paths);
	}
	exit(-1);
}
