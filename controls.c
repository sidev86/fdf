/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:23:00 by sibrahim          #+#    #+#             */
/*   Updated: 2023/04/19 12:23:02 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_pressed(int keycode, t_fdf **fdf)
{
	if (keycode == KEYB_Q || keycode == KEYB_E || keycode == KEYB_A
		|| keycode == KEYB_D || keycode == KEYB_Z || keycode == KEYB_C)
		change_camera_angle(fdf, keycode);
	else if (keycode == KEYB_L_ARROW || keycode == KEYB_R_ARROW
		|| keycode == KEYB_U_ARROW || keycode == KEYB_D_ARROW)
		move_map(fdf, keycode);
	else if (keycode == KEYB_MINUS || keycode == KEYB_PLUS)
		translate_z(fdf, keycode);
	else if (keycode == KEYB_I || keycode == KEYB_P)
		change_projection(fdf, keycode);
	else if (keycode == KEYB_J)
		change_gradient_values(fdf);
	else if (keycode == KEYB_ESC)
	{
		terminate(fdf);
	}
	return (0);
}

static int	mouse_pressed(int mousecode, int x, int y, t_fdf **fdf)
{
	(void)x;
	(void)y;
	if (mousecode == 4)
	{
		if ((*fdf)->cam->zoom < 100)
			(*fdf)->cam->zoom++;
		draw_map(*fdf, (*fdf)->map);
	}
	else if (mousecode == 5)
	{
		if ((*fdf)->cam->zoom > 1)
			(*fdf)->cam->zoom--;
		draw_map(*fdf, (*fdf)->map);
	}
	return (0);
}

void	input_controls(t_fdf **fdf)
{
	mlx_hook((*fdf)->win, 2, (1L << 0), key_pressed, fdf);
	mlx_hook((*fdf)->win, 4, (1L << 2), mouse_pressed, fdf);
	mlx_hook((*fdf)->win, 17, 0, terminate, fdf);
}
