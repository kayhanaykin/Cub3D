/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:41 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/06 11:16:18 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_data *data, int x, int y, char c)
{	
	if (border_check(data, x, y) || data->map_data[y][x] == ' ')
	{
		if (!(c == '1' || c == 'W'))
			error_handler(data, "Error: Unclosed map");
		else
			return ;
	}
	if (data->map_data[y][x] == 'R' || data->map_data[y][x] == 'W')
		return ;
	if (data->map_data[y][x] == '0')
	{
		cross_check(data, x - 1, y - 1);
		cross_check(data, x + 1, y + 1);
		cross_check(data, x - 1, y + 1);
		cross_check(data, x + 1, y - 1);
		data->map_data[y][x] = 'R';
	}
	else if (data->map_data[y][x] == '1')
		data->map_data[y][x] = 'W';
	data->multiple_map_count++;
	flood_fill(data, x - 1, y, data->map_data[y][x]);
	flood_fill(data, x + 1, y, data->map_data[y][x]);
	flood_fill(data, x, y + 1, data->map_data[y][x]);
	flood_fill(data, x, y - 1, data->map_data[y][x]);
}

void	second_map_check(t_data *data)
{
	if (data->multiple_map_count != data->total_char_count)
		error_handler(data, "Multiple maps");
}

void	map_control(t_data *data)
{
	possible_char_check(data);
	data->map_data[(int)data->pos_y][(int)data->pos_x] = '0';
	flood_fill(data, data->pos_x, data->pos_y, '0');
	second_map_check(data);
}

void	cross_check(t_data *data, int x, int y)
{
	if (x == -1 || x == data->max_line_length || y == -1
		|| y == data->line_count)
		error_handler(data, "Unclosed map");
	if (data->map_data[y][x] == ' ')
		error_handler(data, "Unclosed map");
}
