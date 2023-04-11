#include "mlx/mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*void rotation_x(t_point *p, int theta)
{
	p->pos[1] = p->pos[1] * cos(theta) + p->pos[2] * sin(theta);
	p->pos[2] = -p->pos[1] * sin(theta) + p->pos[2] * cos(theta);
}

void rotation_y(t_point *p, int theta)
{
	p->pos[0] = p->pos[0] * cos(theta) + p->pos[2] * sin(theta); 
	p->pos[2] = -p->pos[0] * sin(theta) + p->pos[2] * cos(theta);
}

void rotation_z(t_point *p, int theta)
{
	p->pos[0] = p->pos[0] * cos(theta) - p->pos[1] * sin(theta);
	p->pos[1] = p->pos[0] * sin(theta) + p->pos[1] * cos(theta); 
}*/


void bresenham_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
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
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
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
	y_prev =(*points_map)[y][x].pos[1];

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
	int dist = 20; 
	//printf("%p\n", alt);
	//printf("rws: %d\n", rows);
	if (cols > rows)
		dist = 500 / cols; 
	else 
		dist = 500 / rows; 
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
			(*points_map)[i][j].pos[1] = i * dist; 
			(*points_map)[i][j].pos[0] = j * dist; 
			(*points_map)[i][j].pos[2] = get_altitude_value(alt, i, j);
		
			j++;
		}
		i++;
	}
}

void draw_map(void *mlx_ptr, void *win_ptr, t_point ***points_map, int r, int c)
{

	int i = 0; 
	int j = 0; 
	int x_offset = 450; 
	int y_offset = 300;

	while(i < r)
	{
		j = 0; 
		while (j < c)
		{
			if (i < r-1)
			{
				bresenham_line(mlx_ptr, win_ptr, (*points_map)[i][j].pos[1]+x_offset, (*points_map)[i][j].pos[0]+ y_offset, (*points_map)[i+1][j].pos[1]+x_offset,(*points_map)[i+1][j].pos[0]+y_offset, 0xFFFFFF);
			}
			if (j < c-1)
			{
				bresenham_line(mlx_ptr, win_ptr, (*points_map)[i][j].pos[1]+x_offset, (*points_map)[i][j].pos[0]+ y_offset, (*points_map)[i][j+1].pos[1]+x_offset,(*points_map)[i][j+1].pos[0]+y_offset, 0xFFFFFF);
			}		
			j++;
		}
		i++;
	} 
	//mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

}

int key_pressed(int keycode, t_vars **vars)
{
	printf("Hai premuto il tasto %d\n", keycode);

	if (keycode == 8)
		mlx_clear_window((*vars)->mlx, (*vars)->win);
	else if (keycode == 53)
	{
		mlx_destroy_window((*vars)->mlx, (*vars)->win);
		exit(0); 
	}
	return (0); 
}

int mouse_pressed(int mousecode,int x, int y, t_camera **cam)
{
	
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	if(mousecode == 4){
		
		
		(*cam)->zoom++;
		printf("Camera zoom level = %d\n", (*cam)->zoom);
	}
	else if (mousecode == 5)
	{
		(*cam)->zoom--;
		printf("Camera zoom level = %d\n", (*cam)->zoom);
	}
		
	else if (mousecode == 1)
		printf("Left Click\n");
	return(0); 
}

int	main(int argc, char **argv)
{
	t_vars *vars; 
	
	//t_fdf *fdf; 
	t_point	**points_map;
	t_map	*map;
	t_altitudes *alt; 
	t_camera *cam; 

	if (argc == 2)
	{
		map = malloc(sizeof(t_map));
		vars = malloc(sizeof(t_vars)); 
		cam = malloc(sizeof(t_camera)); 
		cam->zoom = 1; 
		points_map = 0;
		printf("Camera zoomy level = %d\n", cam->zoom);
		//printf("%p\n", points_map);
		alt = 0; 
		vars->mlx = mlx_init(); 
		printf("%s\n", argv[1]);
		
		read_map(argv[1], &map, &alt);
		vars->win  = mlx_new_window(vars->mlx, 1024, 768, "drawtest");
		//printf("%p\n", vars->win);
		
		
		printf("rows = %d cols = %d\n", map->height, map->width);
		
		init_map_points(&points_map, &alt, map->height, map->width);
		isometric_view(&points_map, map->height, map->width);
		draw_map(vars->mlx, vars->win, &points_map, map->height, map->width);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_hook(vars->win, 2, 0, key_pressed, &vars);
		mlx_hook(vars->win, 4, 0, mouse_pressed, &cam); 
		
		mlx_loop(vars->mlx);
	}	
}
