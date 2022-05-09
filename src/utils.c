void	init_map(char *map_path, t_map_data *map_data)
{
	int		fd;
	char	c;
	int		len;

	len = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		err_handling("map couldn't be read");
	while (read(fd, &c, 1))
		len++;
	close(fd);
	map_data->map = (char *)malloc(len + 1);
	map_data->initial_map = (char *)malloc(len + 1);
	if (map_data->map == NULL || map_data->initial_map == NULL)
		err_handling("could not allocte memory for the game.");
	map_data->map_len = len;
	fd = open(map_path, O_RDONLY);
	read(fd, map_data->map, len);
	map_data->map[len] = '\0';
	ft_strlcpy(map_data->initial_map, map_data->map, len);
}