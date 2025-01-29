/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/29 11:42:43 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
    Argümanların kontrolü
*/

int arg_check(int ac, char *av[])
{
    int len;
    
    if (ac != 2)
        return(error_handler(NULL, "Wrong number of arguments"));
    len = ft_strlen(av[1]);
    if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' 
        || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
        return(error_handler(NULL, "Improper file"));
    return (0);
}

/*
    Error handler, mesajı yazdırıp datayı freeleyip exit atıp programı kapatıyoruz
*/

int	error_handler(t_data *data, char *msg)
{
	if (msg != NULL)
    {
        ft_putendl_fd("Error", 2);
		ft_putendl_fd(msg, 2);
    }
	free(msg); //"string literal buraya gelebilir, freeleme sorunu cikabilir kontrol edilmesi lazim"
    //freedata
    exit(1);
	//return (1);
}

/*
    Initialize
*/

void    init(t_data data)
{
    char *meta[6];
    data.meta_data = meta;
}

/*
    Bütün whitespace'leri space ile değiştiriyoruz.
*/

void    replace_white_s_with_s(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\f' ||str[i] == '\r' 
            || str[i] == '\v' || str[i] == '\t')
            str[i] == ' ';
        i++;
    }
    return ;
}

/*
    Wordslerle işimiz bitince freeliyoruz.
*/
void    free_words(char **words)
{
    int i;
    
    i = 0;
    while (words[i])
    {
        free(words[i]);
        i++;
    }
    return ;
}
/*
    Meta dataların kontrolünü yapıyoruz. 6 tane olup olmadığını ve ulaşılabilir ve
    okunabilir olup olmadığını kontrol ediyoruz.
*/

void    check_meta_data(t_data *data)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (data->meta_data[i] == NULL)
            error_handler(data, "Missing or repeated elements");
        if (i < 4 && access(data->meta_data[i], F_OK | R_OK) != 0)
            error_handler(data, "Non-existing or unreadable file");
        i++;
    }
    return ;
}

/*
    Split ile gelen words'leri ilkine bakıp identifier mı diye kontrol ettik.
    Oyleyse bir sonraki wordü data->meta_data'nın uygun yerine koyuyoruz.
	ve bir sonraki kelimenin de olamdığını kontrol ediyoruz, cunku olmamalı"
*/
void    get_element(t_data *data, char **str)
{
    int i;

    i = 0;
    if (str[0][0] == 'N' && str[0][1] == 'O' && str[0][2] == NULL)
        data->meta_data[NO] = str[1];
    else if (str[0][0] == 'S' && str[0][1] == 'O' && str[0][2] == NULL)
        data->meta_data[SO] = str[1];
    else if (str[0][0] == 'W' && str[0][1] == 'E' && str[0][2] == NULL)
        data->meta_data[WE] = str[1];
    else if (str[0][0] == 'E' && str[0][1] == 'A' && str[0][2] == NULL)
        data->meta_data[EA] = str[1];
    else if (str[0][0] == 'F' && str[0][1] == NULL)
        data->meta_data[F] = str[1];
    else if (str[0][0] == 'C' && str[0][1] == NULL)
        data->meta_data[C] = str[1];
    if (str[2] != NULL)
        error_handler(data, "Excessive information");
}

int		all_white_space(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!(str[i] == '\f' || str[i] == '\r' 
            || str[i] == '\v' || str[i] == '\t' || str[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

//whitespace check yapıyoruz bir karakter üzerinden
int	white_space_check(char c)
{
	if (!(c == '\f' || c == '\r' 
        || c == '\v' || c == '\t' || c == '\n'))
		return (1);
	return (0);
}

void    get_map_size(t_data *data, int fd)
{
    char    *line;
    int     i;

    line = malloc(1);  //niye yapiyorduk?
	if (line == NULL)
		error_handler(data, "Error: Allocation Error");
	while (1) // white space kontrolü yaptık harita gelmeden onceki bos satirlari atladik
	{
		line = get_next_line(fd);
		if (!all_white_space(line))
			break;
	}
    while(line) //yukaridaki while'da haritanın ilk satırını alarak başladığımız için burada get_next_line'ı dongünün sonuna koyduk
    {
        data->line_count++;
        if (ft_strlen(line) > data->max_line_length)
            data->max_line_length = ft_strlen(line);
		// if (!all_white_space(line))
		// {
		// 	data->line_count--;
		// 	break ;
		// }
        free (line);
        line = get_next_line(fd);
    }
    close (fd);
    data->map_data = malloc (sizeof(char *) * (data->line_count));  //second map icin malloc yapilabilir
	if (data->map_data == NULL)
		error_handler(data, "Error: Allocation Error");
    i = 0;
    while (i < data->line_count)
        data->map_data[i++] = ft_calloc(data->max_line_length, sizeof(char));
}


void    get_meta_data(t_data *data, int fd)
{
    int     count;
    char    *line;
    char    **words;
    
    count = -1;
    while (count < 6)
    {
        line = get_next_line(fd);
        replace_white_s_with_s(line);
        words = ft_split(line, ' ');
        if (words[0] == NULL)
            continue ;
        get_element(data, words);
        count++;
        free_words(words);
    }
    if (count != 6)
        check_meta_data(data);
}

void    get_map_data(t_data *data, int fd)
{
    char    *line;
    int     i;

    line = malloc(1);
    i = 0;
	while (1) // white space kontrolü yaptık harita gelmeden onceki bos satirlari atladik
	{
		line = get_next_line(fd);
		if (!all_white_space(line))
			break;
	}
    while (line)
    {
        copy_line(data->map_data, line, i);
        i++;
		free(line);
        line = get_next_line(fd);
    }
}

void    copy_line(char **map_data, char *line, int line_no)
{
    int i;

    i = 0;
    while (line[i])
    {
        map_data[line_no][i] = line[i];
        i++;
    }
	map_data[line_no][i] = '\0';
}

void    parser(t_data *data, char *av)
{
    int     fd;
    fd = open(av, O_RDONLY);
    
    get_meta_data(data, fd);
    get_map_size(data, fd);
    fd = open(av, O_RDONLY);
    get_meta_data(data, fd); //offseti haritanın başına getiriyoruz
    get_map_data(data, fd);
}

int	player_pos_finder(t_data *data, char c) //gelen harfe gore baktigi yonu belirleyip acisini aldik, invalid char gelirse hata veriyoruz
{
	static int counter;

	if (c == '0' || c == '1')
		return (0);
	else if (c == 'N')
		data->pos_angle = 0;
	else if (c == 'E')
		data->pos_angle = 90;
	else if (c == 'S')
		data->pos_angle = 180;
	else if (c == 'W')
		data->pos_angle = 270;
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
			if (player_pos_finder(data, data->map_data[i][j])) //pozisyonu alıyoruz
			{
				data->pos_x = j;
				data->pos_y = i;
			}
			if (!white_space_check(data->map_data[i][j]))
				data->total_char_count++;
			j++;
		}
		i++;
	}
}

void	flood_fill(t_data *data, int x, int y, char c) //koselerin kapalı olma durumunu kontrol ettik, recursion olusturduk
{	
	data->multiple_map_count++;
	if (border_check(data, x, y) || ws_check(data, x, y))
		if(c != '1')
			error_handler(data, "Unclosed map");
		else
			return ;
	// if (border_check(data, x, y) && c != '1')
	// 	error_handler(data, "Unclosed map");
	// else if (border_check(data, x, y) && c == '1')  //kose/kenar ve duvarsa recursion bitecek.
	// 	return ;
	// if (ws_check(data, x, y) && c != '1')
	// 	error_handler(data, "Unclosed map");
	// else if (ws_check(data, x, y) && c == '1')  //kose/kenar ve duvarsa recursion bitecek.
	// 	return ;
	flood_fil(data, x - 1, y, data->map_data[y][x]); //sol
	flood_fil(data, x , y + 1, data->map_data[y][x]); //aşağı
	flood_fil(data, x + 1, y, data->map_data[y][x]); //sağ
	flood_fil(data, x, y - 1, data->map_data[y][x]);  //üst
}

int	border_check(t_data *data, int x, int y) // kose kontrolu yaptik
{
	if (x == 0 || x == data->max_line_length - 1)
		return (1);
	else if (y == 0 || y == data->line_count - 1)
		return (2);
	else
		return (0);
}


void	second_map_check(t_data *data)
{
	if (data->multiple_map_count != data->total_char_count)
		error_handler(data, "Error: Multiple maps");
}

void	map_control(t_data *data)
{
	possible_char_check(data);
	flood_fill(data, data->pos_x, data->pos_y, 0);
	second_map_check(data);
}


int main(int ac, char *av[])
{
    t_data  data;
    if (arg_check(ac, av))
        return (1);
    init();  //data struct initi, yapilacak
    parser(&data, av);
	map_control(&data);
    mlx_handle();
    init_win();
    prep_map_for_rc();
    ray_casting();
    mlx_loop();

    return (0);
}
