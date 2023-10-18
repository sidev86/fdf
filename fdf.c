/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:24:30 by sibrahim          #+#    #+#             */
/*   Updated: 2023/04/19 12:24:32 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf		*fdf;
	t_map		*map;
	t_altitudes	*alt;

	if (argc == 2)
	{
		map = init_map();
		alt = 0;
		if (read_map(argv[1], &map, &alt) == -1)
			error_message("Error! File map not found\n");
		fdf = init_fdf(map);
		stack_to_arrays(&alt, map);
		fdf->cam = init_camera(fdf);
		fdf->alt = alt;
		draw_map(fdf, fdf->map);
		input_controls(&fdf);
		mlx_loop(fdf->mlx);
	}	
}
