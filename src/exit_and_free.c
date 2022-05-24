/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:39:12 by tlemma            #+#    #+#             */
/*   Updated: 2022/05/24 19:39:13 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, t_data *data)
{
	int	i;

	i = 0;
	printf("ERROR!\n%s\n", msg);
	while (data->txt_paths[i])
		free(data->txt_paths[i++]);
	if (data->free_map)
		free_2d(data->free_map);
	exit(-1);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(data->txt_paths[i]);
		mlx_delete_texture(data->textures[i]);
		i++;
	}
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

int	cub_exit(t_data *data)
{
	free_textures(data);
	free_2d(data->free_map);
	mlx_delete_image(data->window.mlx, data->window.window);
	mlx_close_window(data->window.mlx);
	mlx_terminate(data->window.mlx);
	return (EXIT_SUCCESS);
}
