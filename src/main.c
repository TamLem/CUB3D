/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:18:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/21 16:11:55 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, t_data *data)
{
	printf("ERROR!\n%s\n", msg);
	// if (data->map)
	// 	free_2d(data->map);
	exit(-1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		error_msg(
			"Please execute with './cub3D path/to/map/MAPNAME.cub'.", &data);
	}
	else if (parse_map(&data, argv[1]) && load_texture(&data))
		raycaster(&data);
	return (0);
}
