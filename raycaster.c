/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:59:39 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/11 21:44:44 by kaykin           ###   ########.fr       */
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
		if (abs(data->sidedistx) < abs(data->sidedisty))
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			if (data->stepx == -100)
				data->side = E;
			else
				data->side = W;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			if (data->stepy == -100)
				data->side = S;
			else
				data->side = N;
		}
		printf("data->mapy:%d, data->mapx:%d\n", data->mapy,data->mapx);
		if (data->map_data[data->mapy][data->mapx] == 'W')
			data->hit = 1;
	}
	data->hit = 0;
	perpwalldist_calc(data);
}

void	raydir_unitize(t_data *data)
{
	double	len;

	len = sqrt((data->raydirx * data->raydirx)
			+ (data->raydiry * data->raydiry));
	data->raydirx /= len;
	data->raydiry /= len;
}

void	calculate_step(t_data *data)
{
	data->mapx = data->pos_x / 100;
	data->mapy = data->pos_y / 100;
	if (data->raydirx < 0)
	{
		data->stepx = -100;
		data->sidedistx = (data->pos_x - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 100;
		data->sidedistx = (data->mapx + 100 - data->pos_x) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -100;
		data->sidedisty = (data->pos_y - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 100;
		data->sidedisty = (data->mapy + 100 - data->pos_y) * data->deltadisty;
	}
}

void	set_wall(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->window_width)
	{
		data->camerax = 200 * x / (float)data->window_width - 100;
		data->raydirx = data->dirx + data->planex * data->camerax;
		data->raydiry = data->diry + data->planey * data->camerax;
		data->deltadistx = abs(100 / data->raydirx);
		data->deltadisty = abs(100 / data->raydiry);
		calculate_step(data);
		raycaster(data);
		put_vertical_line(data, x);
		x++;
		if (x == 720)
		{
			printf("data->perpwalldist%d\n", data->perpwalldist);
		}
	}	
}
