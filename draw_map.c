#include "fdf.h"

void put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel; 
	int		i;
	
	if (x >= 250 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		i = fdf->bpp - 8; 
		pixel = fdf->data_addr + (y * fdf->line_width + x * fdf->bpp / 8);
		while(i >= 0)
		{
			if (fdf->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (fdf->bpp - 8 - i)) & 0xFF;
			i -= 8; 
		}
	}
	
}

void	draw_line(t_point a, t_point b, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		e1;
	int		e2;

	delta.x = abs(b.x - a.x);
	delta.y = abs(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	e1 = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		put_pixel(fdf, cur.x, cur.y, get_color(cur, a, b, delta));
		if ((e2 = e1 * 2) > -delta.y)
		{
			e1 -= delta.y;
			cur.x += sign.x;
		}
		if (e2 < delta.x)
		{
			e1 += delta.x;
			cur.y += sign.y;
		}
	}
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}

void draw_background(t_fdf *fdf)
{
	int	*image;
	int	i;

	ft_bzero(fdf->data_addr, W_WIDTH * W_HEIGHT * (fdf->bpp / 8));
	image = (int *)(fdf->data_addr);
	i = 0;
	while (i < W_HEIGHT * W_WIDTH)
	{
		image[i] = (i % W_WIDTH < M_WIDTH) ? MENU_COLOR : 0x000020;
		i++;
	}
}


void draw_map(t_fdf *fdf, t_map *map)
{
	int x; 
	int y;

	y = 0; 
    draw_background(fdf);  
	while(y < map->height)
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







