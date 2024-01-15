/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:35:07 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/15 13:43:05 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO
// Makefile a revoir
// revoir #includes debut de fichiers (stdio, only fdf.h)
// IOT core dumped when spaces at end of file lines

void	ft_err(int argc, char *argv)
{
	int	len;
	int	fd;

	if (argc == 1 || argc > 2)
		exit (1);
	len = ft_strlen(argv) - 4;
	if (len < 1)
		exit (1);
	if (argv[len] != '.' || argv[len + 1] != 'f'
		|| argv[len + 2] != 'd' || argv[len + 3] != 'f')
		exit (1);
	fd = open(argv, O_RDONLY);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	ft_err(argc, argv[1]);
	map = malloc(sizeof(t_map));
	ft_maptotab(argv[1], map);
	ft_init_map(map, argv);
	mlx_image_to_window(map->mlx_ptr, map->mlx_img, 0, 0);
	ft_draw_map(map);
	mlx_key_hook(map->mlx_ptr, &ft_mod_key, map);
	mlx_scroll_hook(map->mlx_ptr, &ft_mod_scroll, map);
	mlx_loop(map->mlx_ptr);
	mlx_terminate(map->mlx_ptr);
	ft_freetab(map->altitude, map->height);
	free(map);
	return (0);
}
