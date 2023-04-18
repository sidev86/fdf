#include "fdf.h"

void	print_menu(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 25, y += 20, TXT_COLOR, "*** MAP CONTROLS ***");
	mlx_string_put(mlx, win, 15, y += 60, TXT_COLOR, "ZOOM: Mouse Scroll");
	mlx_string_put(mlx, win, 15, y += 30, TXT_COLOR, "CHANGE ALTITUDE: +/-");
	mlx_string_put(mlx, win, 60, y += 40, TXT_COLOR, "* ROTATION *");
	mlx_string_put(mlx, win, 15, y += 25, TXT_COLOR, "X-AXIS: Q/E");
	mlx_string_put(mlx, win, 15, y += 25, TXT_COLOR, "Y-AXIS: A/D");
	mlx_string_put(mlx, win, 15, y += 25, TXT_COLOR, "Z-AXIS: Z/C");
	mlx_string_put(mlx, win, 15, y += 40, TXT_COLOR, "CHANGE PROJECTION: I/P");
	mlx_string_put(mlx, win, 15, y += 20, TXT_COLOR, "(Isometric / Parallel)");
	mlx_string_put(mlx, win, 15, y += 30, TXT_COLOR, "RANDOM GRADIENT: J");
	mlx_string_put(mlx, win, 15, y += 20, TXT_COLOR, "(Only works with maps");
	mlx_string_put(mlx, win, 15, y += 20, TXT_COLOR, "without color info)");
	mlx_string_put(mlx, win, W_WIDTH - 110, W_HEIGHT - 30,
		TXT_COLOR, "by sidev86");
}
