/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:01:59 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/05 12:39:44 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double tex_x_coord(t_data *data)
{
    double	wallx;
    int		tex_x;
	double	distance;

	distance = data->perpwalldist;
    if (data->side == E || data->side == W)
	{
		if (data->perpwalldist <= 1)
			distance = 1;
	  	wallx = data->pos_y + distance * data->raydiry;
	}
    else
	{
		if (data->perpwalldist <= 1)
			distance = 1;
	  	wallx = data->pos_x + distance* data->raydirx;
	}

	
    wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)(data->text_width[data->side]));

    if ((data->side == E || data->side == W) && data->raydirx > 0)
		tex_x = data->text_width[data->side] - tex_x - 1;
    if ((data->side == N || data->side == S) && data->raydiry < 0)
		tex_x = data->text_width[data->side] - tex_x - 1;
	return (tex_x);
}


void	put_vertical_line_to_image(t_data *data, int x, int drawstart, int drawend)
{
	char	*dst;
	double	wall_height;
	double	y_ratio;
	double  x_ratio;
	int		tex_x;
	int 	i;
	
	tex_x = tex_x_coord(data);
	i = 0;
	wall_height = drawend - drawstart;
	y_ratio = wall_height / (double) data->text_height[data->side];
	while (i < drawend - drawstart)
	{
		dst = data->addr_ptr + (drawstart + i) * data->size_line + (x * 4);

		
		*(int *) dst = *(int *)(data->text_address[data->side] + ((int)((double)(i) / y_ratio) * //y yonü
		 data->text_width[data->side] * 4) 
		 
		 + (tex_x * 4)); //x yonü		
		i++;
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