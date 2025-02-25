/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:59:39 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/25 18:10:46 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perpwalldist_calc(t_data *data)
{
	if (data->side == W || data->side == E)
		data->perpwalldist = (data->sidedistx - data->deltadistx);
	else
		data->perpwalldist = (data->sidedisty - data->deltadisty);
}

void	raycaster(t_data *data)
{
	while (data->hit == 0)
	{
		if (fabs(data->sidedistx) < fabs(data->sidedisty))
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			if (data->stepx == -1)
				data->side = E;
			else
				data->side = W;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			if (data->stepy == -1)
				data->side = S;
			else
				data->side = N;
		}
		if (data->map_data[data->mapy][data->mapx] == 'W')
			data->hit = 1;
	}
	data->hit = 0;
	perpwalldist_calc(data);
}

void	calculate_step(t_data *data)
{
	data->mapx = floor(data->pos_x);
	data->mapy = floor(data->pos_y);
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->pos_x - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->pos_x) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->pos_y - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->pos_y) * data->deltadisty;
	}
}

void	set_wall(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->window_width)
	{
		data->camerax = 2.0f * x / (float)data->window_width - 1.0f;
		data->raydirx = data->dirx + data->planex * data->camerax;
		data->raydiry = data->diry + data->planey * data->camerax;
		data->deltadistx = fabs(1 / data->raydirx);
		data->deltadisty = fabs(1 / data->raydiry);
		calculate_step(data);
		raycaster(data);
		put_vertical_line(data, x);
		x++;
	}	
}
