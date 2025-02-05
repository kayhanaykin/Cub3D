/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:54:56 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/05 11:55:26 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_pos_finder(t_data *data, char c) //gelen harfe gore baktigi yonu belirleyip acisini aldik, invalid char gelirse hata veriyoruz
{
	static int counter;

	if (c == '0' || c == '1' || c == '\0' || c == ' ')
		return (0);
	else if (c == 'N')
	{
		data->dirx = 0;
		data->diry = -1;
		data->planex = 0.66;
		data->planey = 0;
	}
	else if (c == 'E')
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = 0.66;
	}	
	else if (c == 'S')
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = -0.66;
		data->planey = 0;
	}	
	else if (c == 'W')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -0.66;
	}
	else
        {
		error_handler(data, "Invalid Character");}
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
			if (player_pos_finder(data, data->map_data[i][j])) //pozisyonu alıyoruz
			{
				data->pos_x = j + 0.5f;
				data->pos_y = i + 0.5f;
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

int	border_check(t_data *data, int x, int y) // kose kontrolu yaptik
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

void    cross_check(t_data *data, int x, int y)
{   
    if (x == -1 || x == data->max_line_length || y == -1 ||
            y == data->line_count)
		error_handler(data, "Error: Unclosed map");
    if (data->map_data[y][x] == ' ')
        error_handler(data, "Error: Unclosed map");
}