/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:39:12 by tlemma            #+#    #+#             */
/*   Updated: 2022/05/24 20:18:06 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, t_data *data)
{
	printf("ERROR!\n%s\n", msg);
	if (data->txt_paths[0])
		free(data->txt_paths[0]);
	if (data->txt_paths[1])
		free(data->txt_paths[1]);
	if (data->txt_paths[2])
		free(data->txt_paths[2]);
	if (data->txt_paths[3])
		free(data->txt_paths[3]);
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

int	cub_exit(t_data *data)
{
	free_textures(data);
	free_2d(data->free_map);
	mlx_delete_image(data->window.mlx, data->window.window);
	mlx_close_window(data->window.mlx);
	mlx_terminate(data->window.mlx);
	return (EXIT_SUCCESS);
}
