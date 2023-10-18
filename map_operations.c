/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:25:57 by sibrahim          #+#    #+#             */
/*   Updated: 2023/04/19 12:25:59 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_camera_angle(t_fdf **fdf, int key)
{
	if (key == KEYB_Z)
		(*fdf)->cam->gamma -= 0.05;
	else if (key == KEYB_C)
		(*fdf)->cam->gamma += 0.05;
	else if (key == KEYB_A)
		(*fdf)->cam->beta -= 0.05;
	else if (key == KEYB_D)
		(*fdf)->cam->beta += 0.05;
	else if (key == KEYB_Q)
		(*fdf)->cam->alpha -= 0.05;
	else if (key == KEYB_E)
		(*fdf)->cam->alpha += 0.05;
	draw_map(*fdf, (*fdf)->map);
}

void	change_gradient_values(t_fdf **fdf)
{
	(*fdf)->map->gradient[0] = rand() % 16777215;
	(*fdf)->map->gradient[4] = rand() % 16777215;
	draw_map(*fdf, (*fdf)->map);
}

void	move_map(t_fdf **fdf, int key)
{
	if (key == KEYB_L_ARROW)
		(*fdf)->cam->x_off -= 10;
	else if (key == KEYB_R_ARROW)
		(*fdf)->cam->x_off += 10;
	else if (key == KEYB_D_ARROW)
		(*fdf)->cam->y_off += 10;
	else if (key == KEYB_U_ARROW)
		(*fdf)->cam->y_off -= 10;
	draw_map(*fdf, (*fdf)->map);
}

void	change_projection(t_fdf **fdf, int key)
{
	(*fdf)->cam->alpha = 0;
	(*fdf)->cam->beta = 0;
	(*fdf)->cam->gamma = 0;
	if (key == KEYB_I)
		(*fdf)->cam->iso_active = 1;
	else if (key == KEYB_P)
		(*fdf)->cam->iso_active = 0;
	draw_map(*fdf, (*fdf)->map);
}

void	translate_z(t_fdf **fdf, int key)
{
	if (key == KEYB_PLUS)
		(*fdf)->cam->z_div -= 0.2;
	else if (key == KEYB_MINUS)
		(*fdf)->cam->z_div += 0.2;
	if ((*fdf)->cam->z_div < 0.2)
		(*fdf)->cam->z_div = 0.2;
	if ((*fdf)->cam->z_div > 5)
		(*fdf)->cam->z_div = 5;
	draw_map(*fdf, (*fdf)->map);
}
