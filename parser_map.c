/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:49:04 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/07 16:01:54 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_empty_line(char **line, int fd)
{
	while (1)
	{
		*line = get_next_line(fd);
		replace_white_s_with_s(*line);
		if (!all_white_space(*line))
		{
			break ;
		}
		free(*line);
		*line = NULL;
	}
}

void	get_map_size(t_data *data, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	skip_empty_line(&line, fd);
	while (line)
	{
		data->line_count++;
		if (ft_strlen(line) > data->max_line_length)
			data->max_line_length = ft_strlen(line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
		replace_white_s_with_s(line);
	}
	data->map_data = malloc (sizeof(char *) * (data->line_count));
	if (data->map_data == NULL)
		error_handler(data, "Allocation Error");
	i = 0;
	while (i < data->line_count)
	{
		data->map_data[i] = ft_calloc(data->max_line_length, sizeof(char));
		i++;
	}
}

void	get_map_data(t_data *data, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		replace_white_s_with_s(line);
		if (!all_white_space(line))
			break ;
		free(line);
		line = NULL;
	}
	while (line)
	{
		copy_line(data->map_data, line, i);
		i++;
		free(line);
		line = NULL;
		line = get_next_line(fd);
		replace_white_s_with_s(line);
	}
}

void	map_offset(t_data *data, int fd)
{
	char	*line;

	while (data->offset_line_count--)
	{
		line = get_next_line(fd);
		free(line);
		line = NULL;
	}
}
