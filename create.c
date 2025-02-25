/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:57:51 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/25 16:39:21 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_handler(data, "Mlx display connection cannot be initiated");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window_width,
			data->window_height, "Kuptridi");
	if (!data->win_ptr)
		error_handler(data, "Mlx window cannot be initiated");
	return ;
}

void	create_image(t_data *data)
{
	int	e;

	data->img_ptr = mlx_new_image(data->mlx_ptr,
			data->window_width, data->window_height);
	if (!data->img_ptr)
		error_handler(data, "Mlx image cannot be initiated");
	data->addr_ptr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
			&data->size_line, &e);
	if (!data->addr_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		error_handler(data, "Mlx image properties cannot be fetched");
	}
}

void	create_texture(t_data *data)
{
	int	bpp;
	int	sl;
	int	e;

	data->identifier[NO] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->meta_data[NO], &data->text_width[NO], &data->text_height[NO]);
	data->identifier[SO] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->meta_data[SO], &data->text_width[SO], &data->text_height[SO]);
	data->identifier[WE] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->meta_data[WE], &data->text_width[WE], &data->text_height[WE]);
	data->identifier[EA] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->meta_data[EA], &data->text_width[EA], &data->text_height[EA]);
	data->text_address[NO] = (int *) mlx_get_data_addr(data->identifier[NO],
			&bpp, &sl, &e);
	data->text_address[SO] = (int *) mlx_get_data_addr(data->identifier[SO],
			&bpp, &sl, &e);
	data->text_address[WE] = (int *) mlx_get_data_addr(data->identifier[WE],
			&bpp, &sl, &e);
	data->text_address[EA] = (int *) mlx_get_data_addr(data->identifier[EA],
			&bpp, &sl, &e);
}

int	close_frame(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	error_handler(data, NULL);
	mlx_destroy_display(data->mlx_ptr);
	return (0);
}
