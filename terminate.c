#include "fdf.h"

void    terminate(t_fdf **fdf)
{
        free((*fdf)->map->alt_arr);
		free((*fdf)->map->color_arr);
		free((*fdf)->map);
	    free((*fdf)->cam);
		mlx_destroy_image((*fdf)->mlx, (*fdf)->img);
		mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
		mlx_destroy_display((*fdf)->mlx);
		free((*fdf)->mlx);
		free((*fdf));
		exit(0); 
}