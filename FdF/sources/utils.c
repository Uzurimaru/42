/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:39:09 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/17 18:13:57 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "MLX42/MLX42.h"

size_t	ft_countwords(char *s, char c)
{
	size_t	i;
	size_t	wc;

	wc = 0;
	i = 0;
	if (s[0] == '\n')
		return (0);
	while (s[i + 1] != '\n')
	{
		if (s[i] == c && s[i + 1] != c)
			wc++;
		i++;
	}
	if (s[0] != c && s[0])
		wc++;
	return (wc);
}


void	ft_freetab(int **tab, int height)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_max(float a, float b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	if (a >= b)
		return (a);
	return (b);
}

void	ft_zoom(t_map *map, t_point *orig, t_point *dest)
{
	orig->x = orig->x * map->cam.zoom;
	orig->y = orig->y * map->cam.zoom;
	dest->x = dest->x * map->cam.zoom;
	dest->y = dest->y * map->cam.zoom;
}

void	ft_add_color(t_point *orig, t_point *dest)
{
	orig->col = 0xFFFFFFFF;
	if (orig->z || dest->z)
		orig->col = 0x87CEEBFF;
}

void	ft_put_pixel(t_map *map, t_point pixel)
{
	if (pixel.y > map->win_h || pixel.x > map->win_w || pixel.y < 0 || pixel.x < 0)
		return ;
	mlx_put_pixel(map->mlx_img, pixel.x, pixel.y, pixel.col);
}

#include <stdio.h>

void	ft_shift(t_point *orig, t_point *dest, t_map *map)
{
	printf("\n\tentered ft_shift\n\n");

	printf("\tcam.shift_x: %d\n", map->cam.shift_x);
	printf("\tcam.shift_y: %d\n", map->cam.shift_y);

	orig->x += map->cam.shift_x;
	printf("\tnew orig.x: %f\n", orig->x);

	orig->y += map->cam.shift_y;
	printf("\tnew orig.x: %f\n", orig->y);

	dest->x += map->cam.shift_x;
	printf("\tnew orig.x: %f\n", dest->x);

	dest->y += map->cam.shift_y;
	printf("\tnew orig.x: %f\n", dest->y);
}