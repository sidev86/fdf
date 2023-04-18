#include "fdf.h"

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (placement / distance);
}

int	interpolate(int color1, int color2, double fraction)
{
	unsigned char	r[2];
	unsigned char	g[2];
	unsigned char	b[2];

	r[0] = (color1 >> 16) & 0xff;
	r[1] = (color2 >> 16) & 0xff;
	g[0] = (color1 >> 8) & 0xff;
	g[1] = (color2 >> 8) & 0xff;
	b[0] = color1 & 0xff;
	b[1] = color2 & 0xff;
	return ((int)((r[1] - r[0]) * fraction + r[0]) << 16
		| (int)((g[1] - g[0]) * fraction + g[0]) << 8
		| (int)((b[1] - b[0]) * fraction + b[0]));
}

int	get_default_color(int z, t_map *map)
{
	double	percentage;

	percentage = percent(map->z_min, map->z_max, z);
	return (interpolate(map->gradient[0], map->gradient[4], percentage));
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF,
			end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
