#include "fdf.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}

void	draw_background(t_fdf *fdf)
{
	int	*image;
	int	i;

	ft_bzero(fdf->data_addr, W_WIDTH * W_HEIGHT * (fdf->bpp / 8));
	image = (int *)(fdf->data_addr);
	i = 0;
	while (i < W_HEIGHT * W_WIDTH)
	{
		if (i % W_WIDTH < M_WIDTH)
			image[i] = MENU_COLOR;
		else
			image[i] = 0x000020;
		i++;
	}
}

void	draw_map(t_fdf *fdf, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	draw_background(fdf);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line(projection(point_init(&fdf->map, x, y), fdf),
					projection(point_init(&fdf->map, x + 1, y), fdf), fdf);
			if (y < fdf->map->height -1)
				draw_line(projection(point_init(&fdf->map, x, y), fdf),
					projection(point_init(&fdf->map, x, y + 1), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_menu(fdf);
}
