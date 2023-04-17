#include "fdf.h"

static int key_pressed(int keycode, t_fdf **fdf)
{
	printf("Hai premuto il tasto %d\n", keycode);
	if (keycode == 2 || keycode == 0 || keycode == 6 
	|| keycode == 8 || keycode == 12 || keycode == 14)
		change_camera_angle(fdf, keycode); 
	else if(keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		move_map(fdf, keycode);
	else if(keycode == 30 || keycode == 44)
		translate_z(fdf, keycode);
	else if (keycode == 34 || keycode == 35)
		change_projection(fdf, keycode); 
	else if (keycode == 38)
		change_gradient_values(fdf);
	else if (keycode == 53) //linux -> 65307
	{
		mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
		exit(0); 
	}
	//mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	//draw_map(fdf, &(*fdf)->points_map, (*fdf)->map->height, (*fdf)->map->width);
	return (0); 
}

static int mouse_pressed(int mousecode, int x, int y, t_fdf **fdf)
{
	(void)x;
    (void)y;
	printf("Hai premuto il tasto %d\n", mousecode);
	if(mousecode == 4){
		
		if ((*fdf)->cam->zoom < 100)
			(*fdf)->cam->zoom++;
		printf("Camera zoom level = %d\n", (*fdf)->cam->zoom);
		//mlx_clear_window((*fdf)->mlx, (*fdf)->win);
		draw_map(*fdf, (*fdf)->map);

	}
	else if (mousecode == 5)
	{
		if ((*fdf)->cam->zoom > 1)
			(*fdf)->cam->zoom--;
		//mlx_clear_window((*fdf)->mlx, (*fdf)->win);
		draw_map(*fdf, (*fdf)->map);
		printf("Camera zoom level = %d\n", (*fdf)->cam->zoom);
	}
	else if (mousecode == 1)
		printf("Left Click\n");
	return (0); 
}

void   input_controls(t_fdf **fdf)
{
    mlx_hook((*fdf)->win, 2, (1L<<0), key_pressed, fdf);
	mlx_hook((*fdf)->win, 4, (1L<<2), mouse_pressed, fdf);
}