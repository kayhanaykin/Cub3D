/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:09:14 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/05 15:51:51 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_handler(t_data *data, char *msg)
{
	int		i;
	char	*str;

	i = 0;
	if (msg != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(msg, 2);
	}
	while (i < 6)
		free(data->meta_data[i++]);
	free(data->meta_data);
	i = 0;
	while (i < data->line_count)
		free(data->map_data[i++]);
	free(data->map_data);
	str = get_next_line(data->fd);
	while (str)
	{
		free(str);
		str = get_next_line(data->fd);
	}
	exit(1);
}

int	check_meta_data_inter(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (data->meta_data[i] == NULL)
			break ;
		i++;
	}
	if (i == 6)
		return (1);
	return (0);
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
