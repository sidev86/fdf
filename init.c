#include "fdf.h"

t_map   *init_map(void)
{
    t_map   *map; 
    map = malloc(sizeof(t_map));
    if(!map)
        error_message();
    map->width = 0; 
    map->height = 0; 

    return(map); 
}

t_fdf   *init_fdf(t_map *map)
{
    t_fdf   *fdf; 
    printf("init fdf\n");
    fdf = malloc(sizeof(t_fdf));
   
    if (!fdf)
        error_message();
    fdf->mlx = mlx_init();
    fdf->win = mlx_new_window(fdf->mlx, W_WIDTH, W_HEIGHT, "Fdf");
      printf("qui vaaa?\n");
    fdf->img = mlx_new_image(fdf->mlx, W_WIDTH, W_HEIGHT);
    fdf->map = map;
    fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bpp), &(fdf->line_width), &(fdf->endian));
   
    return(fdf);
}

int get_min(int a, int b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

t_camera    *init_camera(t_fdf *fdf)
{
    t_camera    *cam; 

    cam = malloc(sizeof(t_camera));
    if(!cam)
        error_message();
    cam->zoom = get_min((W_WIDTH / fdf->map->width / 2), (W_HEIGHT / fdf->map->height / 2)); 
    cam->alpha = 0; 
    cam->beta = 0; 
    cam->gamma = 0; 
    cam->x_off = 0; 
    cam->y_off = 0;      
    return (cam);                   
}


t_point	point_init(t_altitudes **alt, int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = get_altitude_value(alt, y, x);
	return (point);
}