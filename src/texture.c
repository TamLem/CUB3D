/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:07:13 by tlemma            #+#    #+#             */
/*   Updated: 2022/05/23 14:07:32 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	load_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures[i] = mlx_load_png(data->txt_paths[i]);
		if (data->textures[i] == NULL)
		{
			while (--i >= 0)
			{
				mlx_delete_texture(data->textures[i]);
			}
			printf("texture load error\n");
			return (false);
		}
		i++;
	}
	return (true);
}
