/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:29:06 by jroth             #+#    #+#             */
/*   Updated: 2022/05/23 17:05:58 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(int r, int g, int b, int t)
{
	return (r << 24 | g << 16 | b << 8 | t);
}

void	error_msg(char *msg, t_data *data)
{
	printf("ERROR!\n%s\n", msg);
	if (data->map)
		free_2d(data->map);
	system("leaks cub3D");
	exit(-1);
}

bool	check_char(const char c)
{
	if (c == '1' || c == '0'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

void	free_2d(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(data->textures[i]);
		i++;
	}
}
