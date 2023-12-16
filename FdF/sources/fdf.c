/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:35:07 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/16 13:22:44 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "MLX42/MLX42.h"

void my_keyhook(mlx_key_data_t keydata, t_map map)
{
	(void) map;
	
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		ft_printf("Hello ");

	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		ft_printf("World");

	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		ft_printf("!");
}

int	main(int argc, char **argv)
{
	t_map	*map;

	(void) argc;
	map = malloc(sizeof(t_map));
	ft_maptotab(argv[1], map);

	ft_printf("\n\nheight: %d\n", map->height);
	ft_printf("width: %d\n", map->width);

	map->cam.zoom = 15;
	map->win_w = 750;
	map->win_h = 500;

	map->mlx_ptr = mlx_init(map->win_w, map->win_h, "FdF", true);

	ft_printf("\ncreated window\n");

	map->mlx_img = mlx_new_image(map->mlx_ptr, map->win_w, map->win_h);
	mlx_image_to_window(map->mlx_ptr, map->mlx_img, 0, 0);

	ft_printf("\ncreated image\n");

	ft_draw_map(map);

	// TODO check how to use mlx_key_hook for bonuses
	// mlx_key_hook(map->mlx_ptr, &ft_mod, map);

	mlx_loop(map->mlx_ptr);
	mlx_terminate(map->mlx_ptr);

	ft_freetab(map->altitude, map->height);
	free(map);
	return (0);
}