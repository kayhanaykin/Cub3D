/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:06:54 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/11 07:40:18 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	atoi_cub3d(t_data *data, const char *str)
{
	int		i;
	int		mult;
	int		nb;
	int		digit_count;

	mult = 1;
	nb = 0;
	i = 0;
	digit_count = 0;
	(void)data;
	while (str && str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			digit_count++;
			nb = (nb * 10) + (str[i] - '0');
		}
		else
			return (-1);
		i++;
	}
	nb *= mult;
	if (digit_count > 3)
		return (-1);
	return (nb);
}

void	check_rgb(t_data *data, char **word)
{
	int	i;

	i = 0;
	while (word[i])
		i++;
	if (i != 3)
	{
		free_words(word);
		error_handler(data, "Incorrect RGB value");
	}
	i = 0;
	while (i < 3)
	{
		if (atoi_cub3d(data, word[i]) < 0 || atoi_cub3d(data, word[i]) > 255)
		{
			free_words(word);
			error_handler(data, "Incorrect RGB value");
		}
		i++;
	}
	if (word[i])
	{
		free_words(word);
		error_handler(data, "Incorrect RGB value");
	}
}

void	comma_check(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->meta_data[F][i])
	{
		if (data->meta_data[F][i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		error_handler(data, "Improper file");
	i = 0;
	count = 0;
	while (data->meta_data[C][i])
	{
		if (data->meta_data[C][i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		error_handler(data, "Improper file");
}

void	get_color(t_data *data)
{
	char	**word;

	comma_check(data);
	word = ft_split(data->meta_data[F], ',');
	check_rgb(data, word);
	data->floor_color = (65536 * ft_atoi(word[0]))
		+ (256 * ft_atoi(word[1])) + (ft_atoi(word[2]));
	free_words(word);
	word = ft_split(data->meta_data[C], ',');
	check_rgb(data, word);
	data->ceiling_color = (65536 * ft_atoi(word[0]))
		+ (256 * ft_atoi(word[1])) + (ft_atoi(word[2]));
	free_words(word);
}
