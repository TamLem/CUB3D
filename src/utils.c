/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:29:06 by jroth             #+#    #+#             */
/*   Updated: 2022/05/20 20:03:00 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(int r, int g, int b, int t)
{
	return (r << 24 | g << 16 | b << 8 | t);
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
