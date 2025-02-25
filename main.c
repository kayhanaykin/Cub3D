/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/25 17:58:40 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_data	data;

	init(&data);
	arg_check(&data, ac, av);
	parser(&data, av[1]);
	map_control(&data);
	create_window(&data);
	create_image(&data);
	create_texture(&data);
	set_background(&data);
	set_wall(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 2, (1L << 0), key_press, &data);
	mlx_hook(data.win_ptr, 17, 0, close_frame, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

void	parser(t_data *data, char *av)
{
	data->fd = open(av, O_RDONLY);
	get_meta_data(data, data->fd);
	get_map_size(data, data->fd);
	close (data->fd);
	data->fd = open(av, O_RDONLY);
	map_offset(data, data->fd);
	get_map_data(data, data->fd);
}

void	init(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->meta_data = ft_calloc(7, sizeof(char *));
	if (!data->meta_data)
		error_handler(data, "Allocation Error");
	data->window_height = 1080;
	data->window_width = 1440;
}

void	arg_check(t_data *data, int ac, char *av[])
{
	int	len;

	if (ac != 2)
		error_handler(data, "Wrong number of arguments");
	len = ft_strlen(av[1]);
	if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u'
		|| av[1][len - 3] != 'c' || av[1][len - 4] != '.')
		error_handler(data, "Improper file");
	if (access(av[1], F_OK | R_OK) != 0)
		error_handler(data, "Non-existing or unreadable file");
	return ;
}
