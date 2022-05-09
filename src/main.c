/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:18:43 by jroth             #+#    #+#             */
/*   Updated: 2022/05/09 17:23:45 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		printf("ERROR! Please execute with './cub3D path/to/map/MAPNAME.cub'.\n");
	else if (parse_map(&data, argv[1]))
	{
		printf("Initialize Game here\n");
	}
	return (0);
}