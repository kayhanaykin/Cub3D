/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:45 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/29 16:15:16 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	do_key(int key, t_data *data);
static void	do_mouse(int key, t_data *data);

int	key_press(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data);
		exit((0));
	}
	if (key == LEFT || key == RIGHT || key == DOWN || key == UP
		|| key == R_ROTATE || key == L_ROTATE)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		do_key(key, data);
		create_image(data);
	}
	return (0);
}

static void	do_key(int key, t_data *data)
{
	// if (key == LEFT)
	// 	data->xshift -= 50;
	// if (key == RIGHT)
	// 	data->xshift += 50;
	// if (key == DOWN)
	// 	data->yshift += 50;
	// if (key == UP)
	// 	data->yshift -= 50;
	// if (key == L_ROTATE)
	// 	data->rotation_angle -= 10;
	// if (key == R_ROTATE)
	// 	data->rotation_angle += 10;
}

