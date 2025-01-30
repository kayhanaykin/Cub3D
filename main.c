/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/30 17:39:49 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
    Argümanların kontrolü
*/

void arg_check(int ac, char *av[])
{
    int len;
    
    if (ac != 2)
       error_handler(NULL, "Wrong number of arguments");
    len = ft_strlen(av[1]);
    if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' 
        || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
        error_handler(NULL, "Improper file");
    return ;
}

/*
    Error handler, mesajı yazdırıp datayı freeleyip exit atıp programı kapatıyoruz
*/

int	error_handler(t_data *data, char *msg)
{
	if (msg != NULL)
    {
		ft_putendl_fd(msg, 2);
    }
	//free(msg); //"string literal buraya gelebilir, freeleme sorunu cikabilir kontrol edilmesi lazim"
    //freedata()
    exit(1);
	//return (1);
}

/*
    Bütün whitespace'leri space ile değiştiriyoruz.
*/

void    replace_white_s_with_s(char *str)
{
    int i;

    i = 0;
    while(str && str[i])
    {
        if(str[i] == '\f' ||str[i] == '\r' 
            || str[i] == '\v' || str[i] == '\t')
            str[i] = ' ';
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
	//printf("str:%d\n", str);
	i = 0;
    if (str[0][0] == 'N' && str[0][1] == 'O')
        data->meta_data[NO] = ft_strdup(str[1]);
    else if (str[0][0] == 'S' && str[0][1] == 'O')
        data->meta_data[SO] = ft_strdup(str[1]);
    else if (str[0][0] == 'W' && str[0][1] == 'E')
        data->meta_data[WE] = ft_strdup(str[1]);
    else if (str[0][0] == 'E' && str[0][1] == 'A')
        data->meta_data[EA] = ft_strdup(str[1]);
    else if (str[0][0] == 'F' && !str[0][1])
        data->meta_data[F] = ft_strdup(str[1]);
    else if (str[0][0] == 'C' && !str[0][1])
        data->meta_data[C] = ft_strdup(str[1]);
    if (str[0][2] && str[2] != NULL)
        error_handler(data, "Excessive information");
}

int		all_white_space(char *str)
{
	int i;
	
	i = 0;
	while (str && str[i])
	{
		if (!(str[i] == '\f' || str[i] == '\r' 
            || str[i] == '\v' || str[i] == '\t' || str[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

//whitespace check yapıyoruz bir karakter üzerinden
int	is_white_space(char c) //ws ise 0 donuyor
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

void	get_color(t_data *data)
{
    //if (str[0] == 'F' || str[0] == 'C')
    //{
        char **word;
        word = ft_split(data->meta_data[F], ',');
        data->floor_color = (65536 * ft_atoi(word[0])) + 
            (256 * ft_atoi(word[1])) + (ft_atoi(word[2]));
        word = ft_split(data->meta_data[C], ',');
        data->ceiling_color = (65536 * ft_atoi(word[0])) + 
            (256 * ft_atoi(word[1])) + (ft_atoi(word[2]));
    //}
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
        replace_white_s_with_s(line);
        //printf("lines:%s\n", line);
        words = ft_split(line, ' ');
        if (!words || words[0] == NULL) 
        //bos satır komple bos olabilir yani null, veya icerisinde white space iceren bir line de olabilr
        // her iki durumda da atlamasi gerekiyor
            continue ;
        get_element(data, words);
        count++;
        free_words(words);
        //printf("count:%d\n", count);
    }
    //printf("check\n");
    if (count != 6)
        check_meta_data(data);
    get_color(data);
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
    //data->map_data[data->pos_y][data->pos_x] = '0';
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

	if (c == '0' || c == '1' || c == '\0' || c == ' ')
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
        {printf("%d\n", c);
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
            //printf("length%d\n", data->max_line_length);
            //printf("ss%c\n", data->map_data[i][j]);
			if (player_pos_finder(data, data->map_data[i][j])) //pozisyonu alıyoruz
			{
				data->pos_x = j;
				data->pos_y = i;
			}
			if (data->map_data[i][j] != '\0' && data->map_data[i][j] != ' ')
				data->total_char_count++;
			j++;
		}
		i++;
	}
}

int	border_check(t_data *data, int x, int y) // kose kontrolu yaptik
{
    printf("--data->max_line_length:%d, data->line_coun: %d\n", data->max_line_length, data->line_count);
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
    printf("--x:%d, y: %d\n", x, y);
    if (x == -1 || x == data->max_line_length || y == -1 ||
            y == data->line_count)
		error_handler(data, "Error: Unclosed map");
    if (data->map_data[y][x] == ' ')
        error_handler(data, "Error: Unclosed map");
}

void	flood_fill(t_data *data, int x, int y, char c) //koselerin kapalı olma durumunu kontrol ettik, recursion olusturduk
{	
	if (border_check(data, x, y) || data->map_data[y][x] == ' ') //wspacecheck girintli harita kontrolü, bosluksa, ws sifir dondutuyor,  giriyor yani
	{
        //printf("--x:%d, y: %d c: %d\n", x, y, c);
           //printf("border:%d\n", border_check(data, x, y));
           // printf("whitespace:%d\n", !white_space_check(data->map_data[y][x]));
          //  printf("--x:%d, y: %d c: %c\n", x, y, c);

		if(!(c == '1' || c == 'W'))
			error_handler(data, "Error: Unclosed map");
		else
			return ;	
	}
    if (data->map_data[y][x] == 'R' || data->map_data[y][x] == 'W')
        return;

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
    int i = 0;
    int j = 0;
    while(i < data->line_count)
    {
        j = 0;
        while(j < data->max_line_length)
        {
           printf("%c",data->map_data[i][j]);
            j++;
        }
        i++;
        printf("\n");
    }
    // printf("multiple_map_count++: %d, x:%d, y:%d\n ",data->multiple_map_count, x, y);
    data->multiple_map_count++;
	flood_fill(data, x - 1, y, data->map_data[y][x]); //sol
	flood_fill(data, x + 1, y, data->map_data[y][x]); //sağ
	flood_fill(data, x , y + 1, data->map_data[y][x]); //aşağı
	flood_fill(data, x, y - 1, data->map_data[y][x]);  //üst
}

void	second_map_check(t_data *data)
{
	if (data->multiple_map_count != data->total_char_count)
		error_handler(data, "Error: Multiple maps");
}

void	map_control(t_data *data)
{
	possible_char_check(data);
    data->map_data[data->pos_y][data->pos_x] = '0';
	flood_fill(data, data->pos_x, data->pos_y, '0');
    printf("multiple%d\n",data->multiple_map_count);
    printf("total%d\n",data->total_char_count);
	second_map_check(data);
}

void    init(t_data *data)
{
    ft_bzero(data, sizeof(t_data));  // Changed from sizeof(data)
    data->meta_data = ft_calloc(6, sizeof(char *));  // Add this line
    if (!data->meta_data)
        error_handler(data, "Error: Allocation Error");
    // Initialize other necessary fields
    data->window_height = 1080;  // Add default values if needed
    data->window_width = 1440;
}

int main(int ac, char *av[])
{
    t_data  data;
    arg_check(ac, av);
    init(&data);  //data struct initi, yapilacak
    parser(&data, av[1]);
	map_control(&data);
	create_window(&data);
	create_image(&data);
	set_background(&data);

    // prep_map_for_rc();
    // ray_casting();

	mlx_hook(data.win_ptr, 2, (1L << 0), key_press, &data);
	mlx_hook(data.win_ptr, 17, 0, close_frame, &data); //maske yazılabilir
	mlx_loop(data.mlx_ptr);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}
// int i = 0;
    // int j = 0;
    // while(i < data->line_count)
    // {
    //     j = 0;
    //     while(j < data->max_line_length)
    //     {
    //        printf("%c",data->map_data[i][j]);
    //         j++;
    //     }
    //     i++;
    //     printf("\n");
    // }