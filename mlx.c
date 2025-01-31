/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:18:59 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/31 14:57:51 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_handler(data, "Error: Mlx display connection cannot be initiated");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window_width,
			data->window_height, "Kuptridi");
	if (!data->win_ptr)
		error_handler(data, "Error: Mlx window cannot be initiated");
	return ;
}
void	create_image(t_data *data)
{
	data->img_ptr = mlx_new_image(data->mlx_ptr,
		data->window_width, data->window_height);
	if (!data->img_ptr)
		error_handler(data, "Error: Mlx image cannot be initiated");
	data->addr_ptr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	if (!data->addr_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		error_handler(data, "Error: Mlx image properties cannot be fetched");
	}

}

void	calculate_step(t_data *data)
{
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
void	put_vertical_line_to_image(t_data *data, int x, int drawstart, int drawend)
{
	char 	*dst;

	while (drawstart < drawend)
	{
		dst = data->addr_ptr + (drawstart - 1) * data->size_line + (x * 4);
		*(unsigned int *) dst = data->sidecolor[data->side];
		drawstart++;
	}
}

void	put_vertical_line(t_data *data, int x)
{
    int lineheight;
    int drawstart;
	int drawend;
	  
	lineheight = (int)(data->window_height / data->perpwalldist);
	drawstart = -lineheight / 2 + data->window_height / 2;
    drawend = lineheight / 2 + data->window_height / 2;
    if(drawstart < 0)
		drawstart = 0;
    if(drawend >= data->window_height)
		drawend = data->window_height - 1;
	put_vertical_line_to_image(data, x, drawstart, drawend);
}

void	set_wall(t_data *data)
{
	int x;

	x = 0;
	int mapX = (int)data->pos_x;
    int mapY = (int)data->pos_y;
	while (x < data->window_width)
	{
		data->camerax = 2 * x / data->window_width - 1;
		data->raydirx = data->dirx + data->planex * data->camerax;
		data->raydiry = data->diry + data->planey * data->camerax;
		calculate_step(data);
		raycaster(data);
		put_vertical_line(data, x);
		x++;
	}
}

void 	set_background(t_data *data)
{
	char 	*dst;
	int		i;

	i = 0;
	while (i < 4 * (data->window_height * data->window_width) / 2)
	{
		dst = data->addr_ptr + i;
		*(unsigned int *) dst = data->ceiling_color;
		i += data->bits_per_pixel / 8; //32 / 8 = 4
	}
	while (i < 4 * (data->window_height * data->window_width))
	{
		dst = data->addr_ptr + i;
		*(unsigned int *) dst = data->floor_color;
		i += data->bits_per_pixel / 8;
	}
}

void	raycaster(t_data *data)
{
	while (data->hit == 0)
    {
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			if (data->stepx == -1)
				data->side = W;
			else
				data->side = E;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			if (data->stepx == -1)
				data->side = N;
			else
				data->side = S;
		}
		if (data->map_data[data->mapx][data->mapy] > 0)
			data->hit = 1;
    }
	if (data->side == W || data->side == E)
		data->perpwalldist = (data->sidedistx - data->deltadistx);
    else          
		data->perpwalldist = (data->sidedisty - data->deltadisty);
}


int	close_frame(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// freedata(data);
	exit(0);
}
	//set_background
	// while (i < (data->window_height * data->window_width) / 2)
	// {
	// 	dst = data->addr_ptr + i;
	// 	*(unsigned int *) dst = data->ceiling_color;
	// 	i += data->bits_per_pixel / 8;
	// }
	// while (i < (data->window_height * data->window_width))
	// {
	// 	dst = data->addr_ptr + i;
	// 	*(unsigned int *) dst = data->floor_color;
	// 	i += data->bits_per_pixel / 8;
	// }