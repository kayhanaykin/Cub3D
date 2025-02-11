/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:54:56 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/11 21:29:43 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_plane_dir(t_data *data, char c)
{
	if (c == 'N')
	{
		data->planex = 66;
		data->planey = 0;
	}
	else if (c == 'E')
	{
		data->planex = 0;
		data->planey = 66;
	}	
	else if (c == 'S')
	{
		data->planex = -66;
		data->planey = 0;
	}	
	else if (c == 'W')
	{
		data->planex = 0;
		data->planey = -66;
	}
}

static void	set_start_dir(t_data *data, char c)
{
	if (c == 'N')
	{
		data->dirx = 0;
		data->diry = -100;
	}
	else if (c == 'E')
	{
		data->dirx = 100;
		data->diry = 0;
	}	
	else if (c == 'S')
	{
		data->dirx = 0;
		data->diry = 100;
	}	
	else if (c == 'W')
	{
		data->dirx = -100;
		data->diry = 0;
	}
	set_plane_dir(data, c);
}

int	player_pos_finder(t_data *data, char c)
{
	static int	counter;

	if (c == '0' || c == '1' || c == '\0' || c == ' ')
		return (0);
	else if (c == 'N')
		set_start_dir(data, 'N');
	else if (c == 'E')
		set_start_dir(data, 'E');
	else if (c == 'S')
		set_start_dir(data, 'S');
	else if (c == 'W')
		set_start_dir(data, 'W');
	else
		error_handler(data, "Invalid Character");
	counter++;
	if (counter > 1)
		error_handler(data, "More than one player");
	return (1);
}

void	possible_char_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->line_count)
	{
		j = 0;
		while (j < data->max_line_length)
		{
			if (player_pos_finder(data, data->map_data[i][j]))
			{
				data->pos_x = j * 100 + 50;
				data->pos_y = i * 100 + 50;
			}
			if (data->map_data[i][j] != '\0' && data->map_data[i][j] != ' ')
				data->total_char_count++;
			j++;
		}
		i++;
	}
	if (data->pos_x == 0)
		error_handler(data, "Non-existing player");
}

int	border_check(t_data *data, int x, int y)
{
	if (x == -1 || x == data->max_line_length)
		return (1);
	else if (y == -1 || y == data->line_count)
		return (2);
	else if (data->map_data[y][x] == '\0')
		return (3);
	else
		return (0);
}
