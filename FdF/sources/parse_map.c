/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:34:27 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/17 17:58:53 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static size_t	ft_get_height(char *file_name)
{
	int		fd;
	char	*line;
	size_t	height;

	fd = open(file_name, O_RDONLY);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static size_t	ft_get_width(char *file_name)
{
	int		fd;
	char	*line;
	size_t	width;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	width = ft_countwords(line, ' ');
	free(line);
	close(fd);
	return (width);
}

static void	ft_pop_alt(int *alt_num, char *line)
{
	char	**splitted;
	int		i;

	splitted = ft_split(line, ' ');
	i = 0;
	while (splitted[i])
	{
		alt_num[i] = ft_atoi(splitted[i]);
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	ft_maptotab(char *file_name, t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	map->height = ft_get_height(file_name);
	map->width = ft_get_width(file_name);

	map->altitude = ft_calloc(sizeof(int *), map->height + 1);
	i = 0;
	while (i < map->height)
		map->altitude[i++] = ft_calloc(sizeof(int), map->width);
	fd = open(file_name, O_RDONLY);
	i = 0;
	line = get_next_line(fd);

	while (line)
	{
		ft_pop_alt(map->altitude[i], line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	map->altitude[i] = NULL;
}


