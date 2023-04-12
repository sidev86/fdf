#include "mlx/mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define		W_WIDTH	1024
#define		W_HEIGHT 768

void rotation_x(t_point *p, int alpha)
{
	int previous_y;

	previous_y = p->pos[0];
	p->pos[0] = previous_y * cos(alpha) + p->pos[2] * sin(alpha);
	p->pos[2] = -previous_y * sin(alpha) + p->pos[2] * cos(alpha);
	
}

/*void rotation_y(t_point *p, int theta)
{
	p->pos[0] = p->pos[0] * cos(theta) + p->pos[2] * sin(theta); 
	p->pos[2] = -p->pos[0] * sin(theta) + p->pos[2] * cos(theta);
}

void rotation_z(t_point *p, int theta)
{
	p->pos[0] = p->pos[0] * cos(theta) - p->pos[1] * sin(theta);
	p->pos[1] = p->pos[0] * sin(theta) + p->pos[1] * cos(theta); 
}*/   

void pixel_put(t_fdf **fdf, int x, int y, int color)
{
	char	*pixel; 
	int		i;
	
	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		i = (*fdf)->img->bpp - 8; 
		pixel = (*fdf)->data_addr + (y * (*fdf)->img->line_width + x * ((*fdf)->img->bpp / 8));
		while(i >= 0)
		{
			if ((*fdf)->img->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> ((*fdf)->img->bpp - 8 - i)) & 0xFF;
			i -= 8; 
		}
	}
	
}
void bresenham_line(t_fdf **fdf, int x1, int y1, int x2, int y2, int color)
{
    int dx = x2 - x1 ;
    int dy = y2 - y1 ;
	int i = 0; 
    int sx1 = 0, sy1 = 0, sx2 = 0, sy2 = 0;

    if (dx < 0)
	{
		sx1 = -1;
		sx2 = -1;
	}
	else if (dx > 0) 
	{
		sx1 = 1;
		sx2 = 1;
	}
	if (dy < 0) 
		sy1 = -1;
	else if (dy > 0) 
		sy1 = 1;
    int longest = abs(dx);
    int shortest = abs(dy);
    if (shortest > longest) 
	{
        longest = abs(dy);
        shortest = abs(dx);
        if (dy < 0) 
			sy2 = -1;
		else if (dy > 0) 
			sy2 = 1;
        sx2 = 0;            
    }
    int	numerator = longest >> 1;
    while (i <= longest) 
	{
       	pixel_put(fdf, x1, y1, color);
        numerator += shortest;
        if (numerator > longest) 
		{
            numerator -= longest;
            x1 += sx1;
            y1 += sy1;
        } 
		else 
		{
            x1 += sx2;
            y1+= sy2;
        }
		i++;
    }
}

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
		root->height = -height; 
		root->next = NULL;
	}
	else
	{
		new = malloc(sizeof(t_altitudes));
		new->y = y;
		new->x = x;
		new->height = -height; 
		curr = *alt;
		while(curr->next)
			curr = curr->next;
		curr->next = new;	
		new->next = NULL;
	}
}

void read_map(char *path, t_map **map, t_altitudes **alt)
{
	int	fd;
	int r = 0;
	int c = 0; 
	char *maprow;
	char **row;
	
	fd = open(path, O_RDONLY);
	if(fd != -1)
	{
		while(1)
		{
			maprow = get_next_line(fd);
			if (maprow)
			{
				row = ft_split(maprow, ' ');
				while(row[c] != 0)
				{
					//printf("%s ", row[c]);
					if (alt == NULL || *alt == NULL)
						*alt = malloc(sizeof(t_altitudes));
					add_altitude_data(alt, r, c, atoi(row[c]));
					
					c++;
				}
				(*map)->width = c;
				r++;
				c = 0; 
			}
			else
			{
				(*map)->height = r;
				close(fd);
				return ;
			}		
		}
	}
	else
	{
		printf("Error! File map not found%d\n", fd);
		exit(0);
	}
		
}

void iso_point(t_point ***points_map, int y, int x)
{
	int x_prev; 
	int y_prev;

	x_prev = (*points_map)[y][x].pos[0];
	y_prev = (*points_map)[y][x].pos[1];

	(*points_map)[y][x].pos[1] = (x_prev - y_prev) * cos(0.523599);
	(*points_map)[y][x].pos[0] = (x_prev + y_prev) * sin(0.523599) + (*points_map)[y][x].pos[2]; 
}

void isometric_view(t_point ***points_map, int rows, int cols)
{
	int	i = 0; 
	int j = 0;
	
	while (i < rows)
	{
		j = 0; 
		while (j < cols)
		{
			iso_point(points_map, i, j);
			j++;
		}
		i++;
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

/*void create_map_points(t_point ***points_map, t_altitudes **alt,  int y, int x)
{
	int c_size = 20; 

	points_map[y][x].pos[0] = y * c_size; 
	points_map[y][x].pos[1] = x * c_size;
	points_map[y][x].pos[2] = get_altitude_value(alt, y, x);
}*/

void init_map_points(t_point ***points_map, t_altitudes **alt, int rows, int cols)
{
	int	i = 0; 
	int j = 0;
	int dist = 50; 
	//printf("%p\n", alt);
	//printf("rws: %d\n", rows);
	
	/*if (cols > rows)
		dist = 500 / cols; 
	else 
		dist = 500 / rows; */
	*points_map = (t_point **)malloc(sizeof(t_point *) * rows); 
	while (i < rows)
	{
		(*points_map)[i] = (t_point *)malloc(sizeof(t_point) * cols);
		i++;
	}
	i = 0; 
	
	while (i < rows)
	{
		j = 0; 
		while (j < cols)
		{

			(*points_map)[i][j].pos[0] = j * dist; 
			(*points_map)[i][j].pos[1] = i * dist; 
			(*points_map)[i][j].pos[2] = get_altitude_value(alt, i, j);

			printf("point pos[0] = %d\n", (*points_map)[i][j].pos[0]);
		
			j++;
		}
		i++;
	}
}

void draw_background(t_fdf **fdf, int color)
{
	int i; 
	int	j; 

	i = 0; 
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
		{
			pixel_put(fdf, j++, i, color);
		}
		++i;
	}
}

void draw_map(t_fdf **fdf, t_point ***points_map, int r, int c)
{

	int i = 0; 
	int j = 0;
	int x_offset = 450; 
	int y_offset = 300;

	mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	draw_background(fdf, 0x000010); 

	while(i < r)
	{
		j = 0; 
		while (j < c)
		{
			rotation_x(&(*fdf)->points_map[i][j] , (*fdf)->cam->alpha);
			printf("cam alphazzz = %f\n", (*fdf)->cam->alpha);
			//printf("pointttt = %d\n", (*points_map)[i][j].pos[0]);
			//(*points_map)[i][j].pos[1] = (*points_map)[i][j].pos[1] * cos((*fdf)->cam->alpha) + (*points_map)[i][j].pos[2] * sin((*fdf)->cam->alpha);
			//(*points_map)[i][j].pos[2]  = -(*points_map)[i][j].pos[1]* sin((*fdf)->cam->alpha) + (*points_map)[i][j].pos[2] * cos((*fdf)->cam->alpha);
			if (i < r - 1)
			{
				bresenham_line(fdf, (*points_map)[i][j].pos[1]* (*fdf)->cam->zoom + x_offset, (*points_map)[i][j].pos[0]* (*fdf)->cam->zoom + y_offset, (*points_map)[i+1][j].pos[1]*(*fdf)->cam->zoom +x_offset,(*points_map)[i+1][j].pos[0]*(*fdf)->cam->zoom +y_offset, 0xFFFFFF);
			}
			if (j < c - 1)
			{
				bresenham_line(fdf, (*points_map)[i][j].pos[1]*(*fdf)->cam->zoom +x_offset, (*points_map)[i][j].pos[0]*(*fdf)->cam->zoom+ y_offset, (*points_map)[i][j+1].pos[1]*(*fdf)->cam->zoom+x_offset,(*points_map)[i][j+1].pos[0]*(*fdf)->cam->zoom+y_offset, 0xFFFFFF);
			}		
			j++;
		}
		i++;
	}

	mlx_put_image_to_window((*fdf)->mlx, (*fdf)->win, (*fdf)->img->mlx_img, 0, 0);

}

void rotate(t_fdf **fdf, int key)
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
		rotate(fdf, keycode); 
	else if (keycode == 53) //linux -> 65307
	{
		mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
		exit(0); 
	}
	mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	draw_map(fdf, &(*fdf)->points_map, (*fdf)->map->height, (*fdf)->map->width);
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
		//printf("Camera zoom level = %d\n", (*fdf)->cam->zoom);
		mlx_clear_window((*fdf)->mlx, (*fdf)->win);
		draw_map(fdf, &(*fdf)->points_map, (*fdf)->map->height, (*fdf)->map->width);

	}
	else if (mousecode == 5)
	{
		if ((*fdf)->cam->zoom > 1)
			(*fdf)->cam->zoom--;
		mlx_clear_window((*fdf)->mlx, (*fdf)->win);
		draw_map(fdf, &(*fdf)->points_map, (*fdf)->map->height, (*fdf)->map->width);
		//printf("Camera zoom level = %d\n", (*fdf)->cam->zoom);
	}
	else if (mousecode == 1)
		printf("Left Click\n");
	return (0); 
}


int	main(int argc, char **argv)
{
	t_fdf *fdf;
	//t_point	**points_map;
	t_altitudes *alt; 

	if (argc == 2)
	{
		fdf = malloc(sizeof(t_fdf)); 
		fdf->map = malloc(sizeof(t_map));
		fdf->cam = malloc(sizeof(t_camera)); 
		fdf->img = malloc(sizeof(t_img));
		fdf->cam->zoom = 1;
		fdf->cam->alpha = 0; 
		fdf->points_map = 0;
		printf("Camera zoomy level = %d\n", fdf->cam->zoom);
		//printf("%p\n", points_map);
		alt = 0; 
		fdf->mlx = mlx_init(); 
		printf("%s\n", argv[1]);
		
		read_map(argv[1], &fdf->map, &alt);
		fdf->win  = mlx_new_window(fdf->mlx, W_WIDTH, W_HEIGHT, "drawtest");
		fdf->img->mlx_img = mlx_new_image(fdf->mlx, W_WIDTH, W_HEIGHT);
		fdf->data_addr = mlx_get_data_addr(fdf->img->mlx_img, &(fdf->img->bpp), &(fdf->img->line_width), &(fdf->img->endian));
		printf("rows = %d cols = %d\n", fdf->map->height, fdf->map->width);
		printf("img addr = %p\n",fdf->data_addr);
		init_map_points(&fdf->points_map, &alt, fdf->map->height, fdf->map->width);
		isometric_view(&fdf->points_map, fdf->map->height, fdf->map->width);
		draw_map(&fdf, &fdf->points_map, fdf->map->height, fdf->map->width);
		mlx_hook(fdf->win, 2, (1L<<0), key_pressed, &fdf);
		mlx_hook(fdf->win, 4, (1L<<2), mouse_pressed, &fdf);
		mlx_loop(fdf->mlx);
		mlx_destroy_image(fdf->mlx, fdf->img->mlx_img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(fdf->mlx);
	}	
}
