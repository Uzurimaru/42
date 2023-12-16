/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:43:17 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/16 13:21:03 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "MLX42/MLX42.h"

void	ft_move(t_map *map, int key)
{
	if (key == MLX_KEY_RIGHT)
		map->cam.shift_x += 10;
	if (key == MLX_KEY_LEFT)
		map->cam.shift_x -= 10;
	if (key == MLX_KEY_DOWN)
		map->cam.shift_y += 10;
	if (key == MLX_KEY_UP)
		map->cam.shift_y -= 10;
}

void	ft_zoom_io(t_map *map, int key)
{
	if (key == MLX_KEY_I)
		map->cam.zoom += 1;
	if (key == MLX_KEY_O)
		map->cam.zoom -= 1;

	// TODO protect against cam.zoom < 1 
}

void	ft_mod(t_map *map, int key)
{
	ft_printf("key pressed: %d\n", key);

	if (key >= MLX_KEY_RIGHT && key <= MLX_KEY_UP)
		ft_move(map, key);
	if (key == MLX_KEY_I || key == MLX_KEY_O)
		ft_zoom_io(map, key);

	// TODO: clear window/image
	// mlx_clear_window(map->mlx_ptr, map->mlx_img); ?
	ft_draw_map(map);
	
}