#include "minilibx/mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void draw_points_row(void *mlx_ptr, void *win_ptr)
{
	int	i = 0; 
	int	j = 0; 
	int	posx = 150; 
	int	posy = 50; 
	while(i < 50)
	{
		j = 0; 
		while(j < 50)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, posx, posy, 0xFF0000);
			posx += 10;
			j++;
		}	
		i++;
		posx = 150; 
		posy += 10;		
	}
}

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

// void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
// {
// 	double dx = x2 - x1;
// 	double dy = y2 - y1; 

// 	int pixels = sqrt((dx * dx) + (dy * dy));
// 	dx /= pixels;
// 	dy /= pixels; 

// 	double pixelX = x1; 
// 	double pixelY = y1;
// 	while (pixels)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, pixelX, pixelY, color);
// 		pixelX += dx;
// 		pixelY += dy;
// 		--pixels;
// 	}
// }

void create_grid_point(t_point	**grid, int y, int x)
{
	t_point *root;
	t_point *new;
	t_point *curr;

	root = *grid;
	if (y == 0 && x == 0)
	{
		//printf("primo punto\n");
		root->y = y;
		root->x = x;
		root->pos[0] = y * 20 + 100;
		root->pos[1] = x * 20 + 100;
		root->next = NULL; 
		//printf("root pos x = %d\n", root->pos[0]);
	}
	else
	{
		//printf("secondo punto\n");
		new = malloc(sizeof(t_point));
		new->y = y;
		new->x = x;
		new->pos[0] = y * 20 + 100;
		new->pos[1] = x * 20 + 100;
		curr = *grid;
		
		while(curr->next != NULL)
		{
			curr = curr->next;
		}
		//printf("curr x = %d\n", curr->x);
		//printf("fine while\n");
		curr->next = new;	
	}
	//printf("fine create\n");
}

void init_grid_points(t_point **grid, int rows, int cols)
{
	int	i = 0; 
	int j = 0;
	
	while (i <= rows)
	{
		j = 0; 
		while (j <= cols)
		{
			if (grid == NULL || *grid == NULL)
				*grid = malloc(sizeof(t_point));
			create_grid_point(grid, i, j);
			j++;
		}
		i++;
	}
	//printf("fine init\n");
	
}

int	*get_next_point_pos(t_point **grid, int y, int x)
{
	t_point *curr;
	int		*pos;
	curr = *grid; 

	pos = malloc(sizeof(int) * 2); 
	while(curr)
	{
		if(curr->y == y && curr->x == x)
		{
			pos[1] = curr->pos[1];
			pos[0] = curr->pos[0];
			break;
		}
		else 
			curr = curr->next;
	}
	return (pos);
}

void draw_grid(void *mlx_ptr, void *win_ptr, t_point **grid, int r, int c)
{
	t_point *curr; 
	int i = 0; 
	int j = 0; 
	int *np_pos; //next point position

	curr = *grid;

	printf ("r = %d c = %d\n", r, c);

	while(i <= r && curr)
	{
		j = 0; 
		while (j <= c && curr)
		{
			if (i < r)
			{
				np_pos = get_next_point_pos(grid, i + 1,j);
				bresenham_line(mlx_ptr, win_ptr, curr->pos[1], curr->pos[0], np_pos[1], np_pos[0], 0xFF0000);
			}
			if (j < c)
			{
				np_pos = get_next_point_pos(grid, i ,j + 1);
				bresenham_line(mlx_ptr, win_ptr, curr->pos[1], curr->pos[0], np_pos[1], np_pos[0], 0xFF0000);
			}	
			j++;	
			curr = curr->next;
		}
		i++;
	} 
	/*printf("curr pos x = %d\n", curr->pos[1]);
	while (curr)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, curr->pos[1], curr->pos[0], 0xFF0000);
		curr = curr->next; 
	}*/
	
	
}


int	*read_map(char *path)
{
	int	fd;
	int r = 0;
	int c = 0; 
	char *maprow;
	char **row;
	int *g_size;

	fd = open(path, O_RDONLY);
	if(fd != -1)
	{
		g_size = malloc(sizeof(int) * 2);
		while(1)
		{
			maprow = get_next_line(fd);
			if (maprow)
			{
				row = ft_split(maprow, ' ');
				while(row[c] != 0)
				{
					printf("%s ", row[c]);
					c++;
				}
				g_size[0] = c;
				r++;
				c = 0; 
			}
			else
			{
				g_size[1] = r;
				printf("row size = %d cols size = %d\n", g_size[1], g_size[0]);
				close(fd);
				return (g_size);
			}		
		}
	}
	return (g_size);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		*matrix_size;
	
	t_point	*grid;

	
	if (argc == 2)
	{
		
		mlx_ptr = mlx_init(); 
		win_ptr = mlx_new_window(mlx_ptr, 800, 600, "drawtest");
		matrix_size = read_map(argv[1]);
		printf("rows = %d cols = %d\n", matrix_size[1], matrix_size[0]);
		grid = 0;
		init_grid_points(&grid, 20, 20);
		//draw_grid(mlx_ptr, win_ptr, &grid, 20, 20);
		
		//bresenham_line(mlx_ptr, win_ptr, 50, 50, 50, 100, 0xFF0000);
		mlx_loop(mlx_ptr);
	}	
}
