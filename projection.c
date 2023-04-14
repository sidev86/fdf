#include "fdf.h"


static void	rotation_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotation_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	rotation_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static void	iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_point     projection(t_point p, t_fdf *fdf)
{
    p.x *= fdf->cam->zoom; 
    p.y *= fdf->cam->zoom; 
    p.z *= fdf->cam->zoom / 2;
    p.x -= (fdf->cam->zoom * fdf->map->width) / 2; 
    p.y -= (fdf->cam->zoom * fdf->map->height) / 2; 
	rotation_x(&p.y, &p.z, fdf->cam->alpha);
    rotation_y(&p.x, &p.z, fdf->cam->beta);
    rotation_z(&p.x, &p.y, fdf->cam->gamma);
    //if (fdf->cam->iso_active == 1)
        iso(&p.x, &p.y, p.z);
    p.x += W_WIDTH / 2 + fdf->cam->x_off;
    p.y += (W_HEIGHT + fdf->map->height * fdf->cam->zoom) / 2 + fdf->cam->y_off;
	return (p); 
}