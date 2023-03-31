#include "minilibx/mlx.h"

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


int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int	posx = 100; 
	int	i = 0; 
	
	mlx_ptr = mlx_init(); 
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "drawtest");
	draw_points_row(mlx_ptr, win_ptr); 
	mlx_loop(mlx_ptr); 


}
