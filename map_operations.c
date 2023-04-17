#include "fdf.h"

void change_camera_angle(t_fdf **fdf, int key)
{
	if(key == 0)
	 	(*fdf)->cam->gamma -= 0.05; 
	else if (key == 2)
		(*fdf)->cam->gamma += 0.05;
	else if (key == 6)
		(*fdf)->cam->beta -= 0.05;
	else if (key == 8)
		(*fdf)->cam->beta += 0.05;
	else if (key == 12)
		(*fdf)->cam->alpha -= 0.05;
	else if (key == 14)
		(*fdf)->cam->alpha += 0.05;
	draw_map(*fdf, (*fdf)->map);
}



void change_gradient_values(t_fdf **fdf)
{
    (*fdf)->map->gradient[0] = rand() % 16777215;
    (*fdf)->map->gradient[4] = rand() % 16777215;
    draw_map(*fdf, (*fdf)->map);
}

void    move_map(t_fdf **fdf, int key)
{
    if(key == 123)
        (*fdf)->cam->x_off -= 10;
    else if (key == 124)
        (*fdf)->cam->x_off += 10;
    else if (key == 125)
        (*fdf)->cam->y_off += 10;
    else if (key == 126)
        (*fdf)->cam->y_off -= 10;
    draw_map(*fdf, (*fdf)->map);
}

void change_projection(t_fdf **fdf, int key)
{
    if (key == 34)
        (*fdf)->cam->iso_active = 1;
    else if (key == 35)
        (*fdf)->cam->iso_active = 0;
      draw_map(*fdf, (*fdf)->map);
}
void    translate_z(t_fdf **fdf, int key)
{
    if (key == 30)
        (*fdf)->cam->z_div -= 0.2;
    else if (key == 44)
        (*fdf)->cam->z_div += 0.2;
    if ((*fdf)->cam->z_div < 0.2)
        (*fdf)->cam->z_div = 0.2;
    if ((*fdf)->cam->z_div > 5)
        (*fdf)->cam->z_div = 5;
    draw_map(*fdf, (*fdf)->map);
}
