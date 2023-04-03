#include "minilibx/mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>

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
	if (y == 0 && x == 0 && !root)
	{
		root = malloc(sizeof(t_point));
		root->y = y;
		root->x = x;
		root->pos[0] = y * 20;
		root->pos[0] = x * 20;
	}
		
	else
	{
		new = malloc(sizeof(t_point));
		new->y = y;
		new->x = x;
		new->pos[0] = y * 20;
		new->pos[1] = x * 20;
		curr = root;
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = new;	
	}
	
}

void init_grid_points(t_point **grid, int rows, int cols)
{
	int	i = 0; 
	int j = 0;
	
	while (i < rows)
	{
		while (j < cols)
		{
			create_grid_point(grid, i, j);
			j++;
		}
		i++;
	}
}


int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int	i = 0; 
	int rows = 5; 
	int cols = 5;
	t_point	*grid;

	grid = 0;
	init_grid_points(&grid, rows, cols);
	draw_grid_points()
	mlx_ptr = mlx_init(); 
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "drawtest");
	mlx_loop(mlx_ptr);
}
