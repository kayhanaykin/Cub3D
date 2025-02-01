/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:45 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/01 15:20:50 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	sway_sign(t_data *data) //default sol
// {
// 	if (data->dirx < 0)
// 	{
// 		if (data->diry < 0)
// 		{
// 			data->sign_x = 1;
// 			data->sign_y = -1;
// 			printf("a\n");
// 		}
// 		else
// 		{
// 			data->sign_x = 1;
// 			data->sign_y = -1;
// 			printf("b\n");
// 		}
// 	}
// 	else
// 	{
// 		if (data->diry < 0)
// 		{
// 			data->sign_x = 1;
// 			data->sign_y = -1;
// 			printf("c\n");
// 		}
// 		else
// 		{
// 			data->sign_x = 1;
// 			data->sign_y = -1;
// 			printf("d\n");
// 		}
// 	}
// }

static void	do_key(int key, t_data *data)
{
	double	olddirx;
	double	rotspeed;
	double	oldplanex;

	rotspeed = 0.1;
	if (key == LEFT)
	{
		data->pos_x += data->diry * 0.1;
		data->pos_y += -1 * data->dirx * 0.1;
	}
	if (key == RIGHT)
	{
		data->pos_x += -1  * data->diry * 0.1;
		data->pos_y += data->dirx * 0.1;
	}
	if (key == DOWN)
	{
		data->pos_x -= data->dirx * 0.1;
		data->pos_y -= data->diry * 0.1;
	}
	if (key == UP)
	{
		data->pos_x += data->dirx * 0.1;
		data->pos_y += data->diry * 0.1;
	}
	if (key == L_ROTATE)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(rotspeed) - data->diry * sin(rotspeed);
		data->diry = olddirx * sin(rotspeed) + data->diry * cos(rotspeed);
		oldplanex = data->planex;
		data->planex = data->planex * cos(rotspeed) - data->planey * sin(rotspeed);
		data->planey = oldplanex * sin(rotspeed) + data->planey * cos(rotspeed);
	}
	if (key == R_ROTATE)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-rotspeed) - data->diry * sin(-rotspeed);
		data->diry = olddirx * sin(-rotspeed) + data->diry * cos(-rotspeed);
		oldplanex = data->planex;
		data->planex = data->planex * cos(-rotspeed) - data->planey * sin(-rotspeed);
		data->planey = oldplanex * sin(-rotspeed) + data->planey * cos(-rotspeed);
	}
}
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
		set_background(data);
		set_wall(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	}
	return (0);
}


