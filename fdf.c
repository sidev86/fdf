
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>




void	add_altitude_data(t_altitudes **alt, int y, int x, int height)
{
	t_altitudes *root;
	t_altitudes *new;
	t_altitudes *curr;

	root = *alt;
	if (y == 0 && x == 0 && root)
	{
		root->y = y;
		root->x = x;
		root->height = height; 
		root->next = NULL;
	}
	else
	{
		new = malloc(sizeof(t_altitudes));
		new->y = y;
		new->x = x;
		new->height = height; 
		curr = *alt;
		while(curr->next)
			curr = curr->next;
		curr->next = new;	
		new->next = NULL;
	}
}

int	get_altitude_value(t_altitudes **alt, int y, int x)
{
	t_altitudes *curr; 

	curr = *alt; 
	while(curr)
	{
		if(curr->y == y && curr->x == x)
		{
			return(curr->height);
		}
		else
			curr = curr->next; 
	}
	return(0); 
}


void change_camera_angle(t_fdf **fdf, int key)
{
	if(key == 2)
	 	(*fdf)->cam->alpha += 0.05; 
	else if (key == 0)
		(*fdf)->cam->alpha -= 0.05; 
	printf ("cam alpha angle = %f", (*fdf)->cam->alpha);
}

int key_pressed(int keycode, t_fdf **fdf)
{
	printf("Hai premuto il tasto %d\n", keycode);

	if (keycode == 8) //linux -> 99
		mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	else if (keycode == 2 || keycode == 0)
		change_camera_angle(fdf, keycode); 
	else if (keycode == 53) //linux -> 65307
	{
		mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
		exit(0); 
	}
	//mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	//draw_map(fdf, &(*fdf)->points_map, (*fdf)->map->height, (*fdf)->map->width);
	return (0); 
}


int mouse_pressed(int mousecode, int x, int y, t_fdf **fdf)
{
	
	//printf("x = %d\n", x);
	//printf("y = %d\n", y);
	x++;
	y++;
	printf("Hai premuto il tasto %d\n", mousecode);
	if(mousecode == 4){
		
		if ((*fdf)->cam->zoom < 40)
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
		//draw_map(fdf, &(*fdf)->points_map, (*fdf)->map->height, (*fdf)->map->width);
		printf("Camera zoom level = %d\n", (*fdf)->cam->zoom);
	}
	else if (mousecode == 1)
		printf("Left Click\n");
	return (0); 
}


int	main(int argc, char **argv)
{
	t_fdf *fdf;
	t_map *map; 

	t_altitudes *alt; 
	//t_point	**points_map;
	if (argc == 2)
	{
		
		map = init_map();
		alt = 0;  
		if (read_map(argv[1], &map, &alt) == -1)
			error_message();
		//printf("Hai finito di leggere??\n");
		fdf = init_fdf(map);
		fdf->cam = init_camera(fdf);
		fdf->alt = alt;
		 
		printf("%s\n", argv[1]);
		draw_map(fdf, fdf->map);
		
		mlx_hook(fdf->win, 2, (1L<<0), key_pressed, &fdf);
		mlx_hook(fdf->win, 4, (1L<<2), mouse_pressed, &fdf);
		mlx_loop(fdf->mlx);
		// mlx_destroy_image(fdf->mlx, fdf->img->mlx_img);
		// mlx_destroy_window(fdf->mlx, fdf->win);
		// free(fdf->mlx);
	}	
}
