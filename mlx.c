/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:18:59 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/30 16:41:45 by kaykin           ###   ########.fr       */
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

void set_background(t_data *data)
{
	char	*dst;
	int		i;

	i = 0;
	while (i < (data->window_height * data->window_width) / 2)
	{
		dst = data->addr_ptr + i;
		*(unsigned int *) dst = data->ceiling_color;
		i += data->bits_per_pixel / 8;
	}
	while (i < (data->window_height * data->window_width))
	{
		dst = data->addr_ptr + i;
		*(unsigned int *) dst = data->floor_color;
		i += data->bits_per_pixel / 8;
	}
}


int	close_frame(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// freedata(data);
	exit(0);
}
