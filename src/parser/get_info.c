/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:46 by jroth             #+#    #+#             */
/*   Updated: 2022/05/09 21:46:32 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	find_color_cf(t_data *data, char *str)
{
	char	**colors;
	int		i;

	i = 0;
	colors = ft_split(str + 2, ',');
	while (colors[i])
		i++;
	if (str[0] == 'C' && i == 3)
	{
		data->c.red = ft_atoi(colors[0]);
		data->c.green = ft_atoi(colors[1]);
		data->c.blue = ft_atoi(colors[2]);
	}
	if (str[0] == 'F' && i == 3)
	{
		data->f.red = ft_atoi(colors[0]);
		data->f.green = ft_atoi(colors[1]);
		data->f.blue = ft_atoi(colors[2]);
	}
	i = -1;
	while (colors[++i])
		free(colors[i]);
	free(colors);
	colors = NULL;
}

void	get_info(t_data *data)
{
	int	i;

	i = -1;
	data->f.green = 0;
	data->f.red = 0;
	data->f.blue = 0;
	data->c.green = 0;
	data->c.red = 0;
	data->c.blue = 0;
	while (data->map[++i])
	{
		if (data->map[i][0] == 'F'
			|| data->map[i][0] == 'C')
			find_color_cf(data, data->map[i]);
	}
}
