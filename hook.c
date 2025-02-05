/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:45 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/05 12:40:53 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	do_key(int key, t_data *data)
{
	double	olddirx;
	double	rotspeed;
	double	oldplanex;
	double	temp_x;
	double	temp_y;
	double 	epsilon;
	float	step_len;
	
	temp_x = data->pos_x;
	temp_y = data->pos_y;
	step_len = 0.1;
	epsilon = 0.5;
	rotspeed = 0.1;
	if (key == LEFT)
	{
		temp_x += data->diry * step_len;
		temp_y += -1 * data->dirx * step_len;
	}
	if (key == RIGHT)
	{
		temp_x += -1  * data->diry * step_len;
		temp_y += data->dirx * step_len;
	}
	if (key == DOWN)
	{
		temp_x -= data->dirx * step_len;
		temp_y -= data->diry * step_len;
	}
	if (key == UP)
	{
		temp_x += data->dirx * step_len;
		temp_y += data->diry * step_len;
	}
	temp_x += data->raydirx * epsilon;
	temp_y += data->raydiry * epsilon;
	if (data->map_data[(int)temp_y][(int)temp_x] != 'W')
	{
		temp_x -= data->raydirx * epsilon;
		temp_y -= data->raydiry * epsilon;
		data->pos_x = temp_x;
		data->pos_y = temp_y;
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
	int	i;

	i = 0;
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		error_handler(data, NULL);
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
		i++;
	}
	return (0);
}

int	close_frame(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	error_handler(data, NULL);
	return (0);
}
