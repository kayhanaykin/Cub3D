/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:45 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/06 13:50:35 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	wall_stop(t_data *data, double *temp_x, double *temp_y)
{
	if (data->dist > 0.1)
	{
		data->pos_x = *temp_x;
		data->pos_y = *temp_y;
	}
}

static void	move_vertical(t_data *data, int key, double *temp_x, double *temp_y)
{
	float	step_len;

	step_len = 0.1;
	if (key == DOWN)
	{
		*temp_x -= data->dirx * step_len;
		*temp_y -= data->diry * step_len;
	}
	if (key == UP)
	{
		*temp_x += data->dirx * step_len;
		*temp_y += data->diry * step_len;
	}
	wall_stop(data, temp_x, temp_y);
}

static void	move_horizontal(t_data *data, int key)
{
	double	temp_x;
	double	temp_y;
	float	step_len;

	step_len = 0.1;
	temp_x = data->pos_x;
	temp_y = data->pos_y;
	if (key == LEFT)
	{
		temp_x += data->diry * step_len;
		temp_y += -1 * data->dirx * step_len;
	}
	if (key == RIGHT)
	{
		temp_x += -1 * data->diry * step_len;
		temp_y += data->dirx * step_len;
	}
	move_vertical(data, key, &temp_x, &temp_y);
}

static void	do_key(int key, t_data *data)
{
	double	olddirx;
	double	rs;
	double	oldplanex;

	rs = 0.1;
	move_horizontal(data, key);
	if (key == L_ROTATE)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(rs) - data->diry * sin(rs);
		data->diry = olddirx * sin(rs) + data->diry * cos(rs);
		oldplanex = data->planex;
		data->planex = data->planex * cos(rs) - data->planey * sin(rs);
		data->planey = oldplanex * sin(rs) + data->planey * cos(rs);
	}
	if (key == R_ROTATE)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-rs) - data->diry * sin(-rs);
		data->diry = olddirx * sin(-rs) + data->diry * cos(-rs);
		oldplanex = data->planex;
		data->planex = data->planex * cos(-rs) - data->planey * sin(-rs);
		data->planey = oldplanex * sin(-rs) + data->planey * cos(-rs);
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
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_ptr, 0, 0);
		i++;
	}
	return (0);
}
