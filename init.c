/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:25:26 by sibrahim          #+#    #+#             */
/*   Updated: 2023/04/19 12:25:29 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error_message("Map Initialization Error!\n");
	map->width = 0;
	map->height = 0;
	map->alt_arr = NULL;
	map->color_arr = NULL;
	map->z_min = FT_INT_MAX;
	map->z_max = FT_INT_MIN;
	map->gradient[0] = COLOR_1;
	map->gradient[4] = COLOR_2;
	return (map);
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		error_message("Fdf Initialization Error\n");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, W_WIDTH, W_HEIGHT, "Fdf");
	fdf->img = mlx_new_image(fdf->mlx, W_WIDTH, W_HEIGHT);
	fdf->map = map;
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bpp),
			&(fdf->line_width), &(fdf->endian));
	return (fdf);
}

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

t_camera	*init_camera(t_fdf *fdf)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		error_message("Camera Initialization Error!\n");
	cam->zoom = get_min(((W_WIDTH - M_WIDTH) / fdf->map->width * 2),
			(W_HEIGHT / (fdf->map->height * 2)));
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->z_div = 1;
	cam->x_off = 0;
	cam->y_off = 0;
	cam->iso_active = 1;
	return (cam);
}

t_point	point_init(t_map **map, int x, int y)
{
	t_point	point;
	int		index;

	index = y * (*map)->width + x;
	point.x = x;
	point.y = y;
	point.z = (*map)->alt_arr[index];
	if ((*map)->color_arr[index] == -1)
		point.color = get_default_color(point.z, *map);
	else
		point.color = (*map)->color_arr[index];
	return (point);
}
