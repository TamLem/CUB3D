/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:18:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/10 15:37:26 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	init_window(mlx_t *mlx)
// {
// 	mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
// 	if (!mlx)
// 		exit(-1);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// }

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		error_msg(
			"Please execute with './cub3D path/to/map/MAPNAME.cub'.", &g_data);
	}
	else if (parse_map(&g_data, argv[1]))
		init();
	return (0);
}
