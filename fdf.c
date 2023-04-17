
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_fdf *fdf;
	t_map *map; 
	t_altitudes *alt; 
	
	if (argc == 2)
	{
		map = init_map();
		alt = 0;  
		if (read_map(argv[1], &map, &alt) == -1)
			error_message();
		fdf = init_fdf(map);
		stack_to_arrays(&alt, map);
		fdf->cam = init_camera(fdf);
		fdf->alt = alt; 
		//printf("%s\n", argv[1]);
		draw_map(fdf, fdf->map);
		input_controls(&fdf);
		mlx_loop(fdf->mlx);
		
	}	
}
