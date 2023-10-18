/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:29:57 by sibrahim          #+#    #+#             */
/*   Updated: 2023/04/19 12:29:58 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	terminate(t_fdf **fdf)
{
	free((*fdf)->map->alt_arr);
	free((*fdf)->map->color_arr);
	free((*fdf)->map);
	free((*fdf)->cam);
	mlx_destroy_image((*fdf)->mlx, (*fdf)->img);
	mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
	mlx_destroy_display((*fdf)->mlx);
	free((*fdf)->mlx);
	free((*fdf));
	exit(0);
}
