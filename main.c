/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/05 14:52:57 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int ac, char *av[])
{
    t_data  data;
    arg_check(ac, av);
    init(&data);  //data struct initi, yapilacak
    parser(&data, av[1]);
	map_control(&data);
	create_window(&data);
	create_image(&data);
    create_texture(&data);
	set_background(&data);
	set_wall(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 2, (1L << 0), key_press, &data);
	mlx_hook(data.win_ptr, 17, 0, close_frame, &data); //maske yazılabilir
	mlx_loop(data.mlx_ptr);
    return (0);
}

void    parser(t_data *data, char *av)
{
    int     fd;
    fd = open(av, O_RDONLY);
    data->fd = fd;
    get_meta_data(data, fd);
    get_map_size(data, fd);
    close (fd);
    fd = open(av, O_RDONLY);
    map_offset(data, fd);
    get_map_data(data, fd); //offseti haritanın başına getiriyoruz
}

void    init(t_data *data)
{
    ft_bzero(data, sizeof(t_data));  // Changed from sizeof(data)
    data->meta_data = ft_calloc(6, sizeof(char *));  // Add this line
    if (!data->meta_data)
        error_handler(data, "Error: Allocation Error");
    // Initialize other necessary fields
    data->window_height = 1440;  // Add default values if needed
    data->window_width = 1440;
    data->offset_line_count = 0;
}

void arg_check(int ac, char *av[])
{
    int len;
    
    if (ac != 2)
       error_handler(NULL, "Wrong number of arguments");
    len = ft_strlen(av[1]);
    if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' 
        || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
        error_handler(NULL, "Improper file");
    if (access(av[1], F_OK | R_OK) != 0)
        error_handler(NULL, "Non-existing or unreadable file");
    return ;
}
