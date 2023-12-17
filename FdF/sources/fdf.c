/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:35:07 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/17 18:19:33 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "MLX42/MLX42.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	(void) argc;
	map = malloc(sizeof(t_map));
	ft_maptotab(argv[1], map);

	ft_printf("\n\nheight: %d\n", map->height);
	ft_printf("width: %d\n", map->width);

	map->win_w = 750;
	map->win_h = 500;

	map->cam.zoom = 15;
	map->cam.shift_x = 10;
	map->cam.shift_y = 7;
	map->cam.scale = 0.12;

	// TODO check why segfault when using cam.angle
	// map->cam.angle = 0.8;

	map->mlx_ptr = mlx_init(map->win_w, map->win_h, "FdF", true);

	ft_printf("\ncreated window\n");

	map->mlx_img = mlx_new_image(map->mlx_ptr, map->win_w, map->win_h);
	mlx_image_to_window(map->mlx_ptr, map->mlx_img, 0, 0);

	ft_printf("\ncreated image\n");

	ft_draw_map(map);

	mlx_key_hook(map->mlx_ptr, &ft_mod_key, map);
	mlx_scroll_hook(map->mlx_ptr, &ft_mod_scroll, map);

	mlx_loop(map->mlx_ptr);
	mlx_terminate(map->mlx_ptr);

	ft_freetab(map->altitude, map->height);
	free(map);
	return (0);
}