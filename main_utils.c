/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:12:00 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/25 16:25:18 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	all_white_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] == '\f' || str[i] == '\r' || str[i] == ' '
				|| str[i] == '\v' || str[i] == '\t' || str[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

int	is_white_space(char c)
{	
	if (!(c == '\f' || c == '\r'
			|| c == '\v' || c == '\t' || c == '\n'))
		return (1);
	return (0);
}

void	copy_line(char **map_data, char *line, int line_no)
{
	int	i;
	int	j;
	int k;

	i = 0;
	k = 0;
	while (line && line[i])
	{
		j = 0;
		if (line[i] == '\t')
		{
			while (j < 8)
			{
				map_data[line_no][k++] = ' ';
				j++;
			}
			i++;
		}
		else
		{
			map_data[line_no][k++] = line[i++];
		}
	}
}

void	replace_white_s_with_s(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\f' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\t'|| str[i] == '\n')
			str[i] = ' ';
		i++;
	}
	return ;
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words && words[i])
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
	return ;
}
