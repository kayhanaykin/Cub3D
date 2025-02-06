/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_meta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:48:18 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/06 11:52:43 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	get_element_search(t_data *data, char **str, int i)
{
	if (str[i][0] == 'N' && str[i][1] == 'O' && !data->meta_data[NO])
		data->meta_data[NO] = ft_strdup(str[i + 1]);
	else if (str[i][0] == 'S' && str[i][1] == 'O' && !data->meta_data[SO])
		data->meta_data[SO] = ft_strdup(str[i + 1]);
	else if (str[i][0] == 'W' && str[i][1] == 'E' && !data->meta_data[WE])
		data->meta_data[WE] = ft_strdup(str[i + 1]);
	else if (str[i][0] == 'E' && str[i][1] == 'A' && !data->meta_data[EA])
		data->meta_data[EA] = ft_strdup(str[i + 1]);
	else if (str[i][0] == 'F' && !str[i][1] && !data->meta_data[F])
		data->meta_data[F] = ft_strdup(str[i + 1]);
	else if (str[i][0] == 'C' && !str[i][1] && !data->meta_data[C])
		data->meta_data[C] = ft_strdup(str[i + 1]);
	else
	{
		free_words(str);
		error_handler(data, "Incorrect Metadata");
	}
}

void	get_element(t_data *data, char **str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		get_element_search(data, str, i);
		i += 2;
	}
	if (str[i])
	{
		free_words(str);
		error_handler(data, "Incorrect Metadata");
	}
}

static int	empty_word_check(char **words)
{
	if (!words || words[0] == NULL)
	{
		free_words(words);
		return (1);
	}
	return (0);
}

void	get_meta_data(t_data *data, int fd)
{
	int		count;
	char	*line;
	char	**words;

	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		data->offset_line_count++;
		replace_white_s_with_s(line);
		words = ft_split(line, ' ');
		free(line);
		if (empty_word_check(words))
			continue ;
		get_element(data, words);
		if (check_meta_data_inter(data, words))
			break ;
		count++;
		free_words(words);
	}
	xpm_check(data);
	check_meta_data(data);
	get_color(data);
}
