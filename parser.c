/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:49:04 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/05 15:22:38 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_element(t_data *data, char **str)
{
    int i;
    
	i = 0;
    while(str[i] && str[i + 1])
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
            error_handler(data, "Incorrect Metadata"); // gelen NO yerine GG olursa patliyor
        }
        i += 2; 
    }
	if (str[i])
    {
        free_words(str);
		error_handler(data, "Incorrect Metadata"); // iki iki aliyor. fakat ucuncu bir  kalıntı vasrsa patliyor NO ./texture/wall_n.xpm SO ./texture/asdasd.xpm d 
    }
}

void    get_meta_data(t_data *data, int fd)
{
    int     count;
    char    *line;
    char    **words;
    
    count = 0;
    while (count < 6)
    {
        line = get_next_line(fd);
        data->offset_line_count++;
        replace_white_s_with_s(line);
        words = ft_split(line, ' ');
        free(line);
        if (!words || words[0] == NULL)
        //bos satır komple bos olabilir yani null, veya icerisinde white space iceren bir line de olabilr
        // her iki durumda da atlamasi gerekiyor
        {
            free_words(words);
            continue ;
        }
        get_element(data, words);
        if (check_meta_data_inter(data))
        {
            free_words(words);
            break ;
        }
        count++;
        free_words(words);
    }
    xpm_check(data);
    check_meta_data(data);
    get_color(data);
}

void    get_map_size(t_data *data, int fd)
{
    char    *line;
    int     i;

	while (1) // white space kontrolü yaptık harita gelmeden onceki bos satirlari atladik
	{
		line = get_next_line(fd);
        replace_white_s_with_s(line);
		if (!all_white_space(line))
			break;
        free(line);
	}
    while(line) //yukaridaki while'da haritanın ilk satırını alarak başladığımız için burada get_next_line'ı dongünün sonuna koyduk
    {
        data->line_count++;
        if (ft_strlen(line) > data->max_line_length)
            data->max_line_length = ft_strlen(line);
        free (line);
        line = get_next_line(fd);
        replace_white_s_with_s(line);
    }
    data->map_data = malloc (sizeof(char *) * (data->line_count));  //second map icin malloc yapilabilir
	if (data->map_data == NULL)
		error_handler(data, "Allocation Error");
    i = 0;
    while (i < data->line_count)
        data->map_data[i++] = ft_calloc(data->max_line_length, sizeof(char));
    line = get_next_line(fd);
    while (line) // get_next_line bufferini temizlemek icin kullaniyoruz. 
    {
        free(line);
        line = get_next_line(fd);
    }
}

void    get_map_data(t_data *data, int fd)
{
    char    *line;
    int     i;

    i = 0;
	while (1) // white space kontrolü yaptık harita gelmeden onceki bos satirlari atladik
	{
		line = get_next_line(fd);
        replace_white_s_with_s(line);
		if (!all_white_space(line))
			break;
        free(line);
	}
    while (line)
    {
        copy_line(data->map_data, line, i);
        i++;
		free(line);
        line = get_next_line(fd);
        replace_white_s_with_s(line);
    }
}

void    map_offset(t_data *data, int fd)
{
    char *line;

    while (data->offset_line_count--)
    {
        line = get_next_line(fd);
        free(line);
    }
}

