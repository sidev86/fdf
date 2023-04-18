#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= 250 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		i = fdf->bpp - 8;
		pixel = fdf->data_addr + (y * fdf->line_width + x * fdf->bpp / 8);
		while (i >= 0)
		{
			if (fdf->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (fdf->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

static t_point	calculate_sign(t_point a, t_point b)
{
	t_point	sign;

	if (a.x < b.x)
		sign.x = 1;
	else
		sign.x = -1;
	if (a.y < b.y)
		sign.y = 1;
	else
		sign.y = -1;
	return (sign);
}

t_point	absolute_delta(t_point a, t_point b)
{
	t_point	delta;

	delta.x = abs(b.x - a.x);
	delta.y = abs(b.y - a.y);
	return (delta);
}

void	draw_line(t_point a, t_point b, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		e1;
	int		e2;

	delta = absolute_delta(a, b);
	sign = calculate_sign(a, b);
	e1 = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		put_pixel(fdf, cur.x, cur.y, get_color(cur, a, b, delta));
		e2 = e1 * 2;
		if (e2 > -delta.y)
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
