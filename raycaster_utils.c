/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:01:59 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/08 13:09:15 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tex_y_coord(t_data *data, double wall_height, int i)
{
	int		tex_y;
	double	y_ratio;
	double	y_offset;

	y_ratio = wall_height / (double) data->text_height[data->side];
	if (data->perpwalldist < 1)
	{
		y_offset = ((1 - data->perpwalldist) / 2)
			* data->text_height[data->side];
		y_ratio /= data->perpwalldist;
	}
	else
		y_offset = 0;
	tex_y = (int)(i / y_ratio + y_offset)
		*(data->text_width[data->side]);
	return (tex_y);
}

double	tex_x_coord(t_data *data)
{
	double	wallx;
	int		tex_x;

	if (data->side == E || data->side == W)
		wallx = data->pos_y + data->perpwalldist * data->raydiry;
	else
		wallx = data->pos_x + data->perpwalldist * data->raydirx;
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)(data->text_width[data->side]));
	return (tex_x);
}

void	put_vertical_line_to_image(t_data *data, int x, int drawstart,
	int drawend)
{
	char	*dst;
	double	wall_height;
	int		tex_x;
	int		tex_y;
	int		i;

	wall_height = drawend - drawstart;
	tex_x = tex_x_coord(data);
	i = 0;
	while (i < drawend - drawstart)
	{
		tex_y = tex_y_coord(data, wall_height, i);
		dst = data->addr_ptr + (drawstart + i) * data->size_line + (x * 4);
		*(int *) dst = *(int *)(data->text_address[data->side]
				+ tex_y * 4 + tex_x * 4);
		i++;
	}
}

void	put_vertical_line(t_data *data, int x)
{	
	int	lineheight;
	int	drawstart;
	int	drawend;

	lineheight = (int)(data->window_height / data->perpwalldist);
	drawstart = -lineheight / 2 + data->window_height / 2;
	drawend = lineheight / 2 + data->window_height / 2;
	if (drawstart < 0)
		drawstart = 0;
	if (drawend >= data->window_height)
		drawend = data->window_height - 1;
	put_vertical_line_to_image(data, x, drawstart, drawend);
}

void	set_background(t_data *data)
{
	char	*dst;
	int		i;

	i = 0;
	while (i < 4 * (data->window_height * data->window_width) / 2)
	{
		dst = data->addr_ptr + i;
		*(int *) dst = data->ceiling_color;
		i += data->bits_per_pixel / 8;
	}
	while (i < 4 * (data->window_height * data->window_width))
	{
		dst = data->addr_ptr + i;
		*(int *) dst = data->floor_color;
		i += data->bits_per_pixel / 8;
	}
}
