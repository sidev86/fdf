#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

void put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel; 
	int		i;
	

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
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


// static void	put_pixel(t_fdf *fdf, int x, int y, int color)
// {
// 	int		i;

// 	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
// 	{
// 		i = (x * fdf->bpp / 8) + (y * fdf->line_width);
// 		fdf->data_addr[i] = color;
// 		fdf->data_addr[++i] = color >> 8;
// 		fdf->data_addr[++i] = color >> 16;
// 	}
// }

void	draw_line(t_point f, t_point s, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		e1;
	int		e2;

	delta.x = abs(s.x - f.x);
	delta.y = abs(s.y - f.y);
	sign.x = f.x < s.x ? 1 : -1;
	sign.y = f.y < s.y ? 1 : -1;
	e1 = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		put_pixel(fdf, cur.x, cur.y, 0xFFFFFF);
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

void draw_background(t_fdf *fdf, int color)
{
	int i; 
	int	j; 

	i = 0; 
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
		{
			put_pixel(fdf, j++, i, color);
		}
		++i;
	}
}

void draw_map(t_fdf *fdf, t_map *map)
{

	int x = 0; 
	int y;
	//map->height = map->height + 0;
    draw_background(fdf, 0x000010); 
	printf("disegno background\n");
    y = 0; 
	while(y <= map->height)
	{
		x = 0; 
		while (x <= map->width)
		{
			if (x < fdf->map->width)
			{
				draw_line(projection(point_init(&fdf->alt, x, y), fdf), projection(point_init(&fdf->alt, x + 1, y), fdf), fdf);
			}
			if (y < fdf->map->height)
			{
				draw_line(projection(point_init(&fdf->alt, x, y), fdf), projection(point_init(&fdf->alt, x, y + 1), fdf), fdf);
			}		
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}







