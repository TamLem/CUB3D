/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:29:06 by jroth             #+#    #+#             */
/*   Updated: 2022/05/20 17:06:53 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

bool	check_line__(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && (str[i] == ' ' || str[i] == '1'))
	{
		if (str[i] == '1')
			return (true);
	}
	return (false);
}

void	find_map_start(char ***map)
{
	int	k;

	k = 0;
	while (*map)
	{
		if (check_line__(*(*map + 1)))
			break ;
		free(**map);
		**map = NULL;
		(*map)++;
	}
}
