/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:09:14 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/25 12:07:49 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	int		i;

	i = 0;
	while (data->meta_data[i] && i < 6)
	{
		free(data->meta_data[i]);
		data->meta_data[i] = NULL;
		i++;
	}	
	free(data->meta_data);
	data->meta_data = NULL;
	i = 0;
	while (i < data->line_count)
	{
		free(data->map_data[i]);
		data->map_data[i] = NULL;
		i++;
	}
	free(data->map_data);
	data->map_data = NULL;
}

void	error_handler(t_data *data, char *msg)
{
	char	*str;

	if (msg != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(msg, 2);
	}
	free_data(data);
	str = get_next_line(data->fd);
	while (str)
	{
		free(str);
		str = NULL;
		str = get_next_line(data->fd);
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->identifier[0]);
		mlx_destroy_image(data->mlx_ptr, data->identifier[1]);
		mlx_destroy_image(data->mlx_ptr, data->identifier[2]);
		mlx_destroy_image(data->mlx_ptr, data->identifier[3]);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(1);
}

void	check_meta_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (data->meta_data[i] == NULL)
			error_handler(data, "Incorrect Metadata");
		if (i < 4 && access(data->meta_data[i], F_OK | R_OK) != 0)
			error_handler(data, "Non-existing or unreadable file");
		i++;
	}
	return ;
}

void	extension_access_check(t_data *data, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 5 || str[len - 1] != 'm' || str[len - 2] != 'p'
		|| str[len - 3] != 'x' || str[len - 4] != '.')
		error_handler(data, "Improper file");
}

void	xpm_check(t_data *data)
{
	extension_access_check(data, data->meta_data[NO]);
	extension_access_check(data, data->meta_data[SO]);
	extension_access_check(data, data->meta_data[WE]);
	extension_access_check(data, data->meta_data[EA]);
}
